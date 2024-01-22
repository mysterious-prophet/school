from collections import deque
from collections import namedtuple

from Automaton_base_class import AutomatonSearch
from Automaton_base_class import datetime

NOT_SET = -1

class Node(object):

	def __init__(self, character, depth, parent):
		self.character = character
		self.depth = depth
		self.word = None
		self.parent = parent
		self.ACsuffix_link = None
		self.ACoutput_link = None
		self.children = {}


class CWNode(Node):

	def __init__(self, character, depth, parent):
		Node.__init__(self, character, depth, parent)
		self.min_difference_s1 = NOT_SET
		self.min_difference_s2 = NOT_SET
		self.CWsuffix_link = None
		self.CWoutput_link = None
		self.shift1 = None
		self.shift2 = None


class Trie(AutomatonSearch):
	
	def create_node(self, character, depth, parent):
		return Node(character, depth, parent)


	def __init__(self):
		""" Initializes Trie class
		"""
		self.size = 0
		self.root = self.create_node(None, 0, None)	#char doesn't exist for root


	def add_word(self, word):
		# The word is being added char by char backwards
		current_node = self.root
		current_depth = 1
		for character in word:
			# Initial state (current_node is root): get the child that contains the character
			next_node = current_node.children.get(character)

			# If the is no such child (next_node is None), then create next_node with current_node as the parent 
			# and add next_node as a child with the character as the index of the dictionary or set 
			# -> (A dictionary is a list of key-value pairs, with unique keys)
			if not next_node:
				next_node = self.create_node(character, current_depth, current_node)
				current_node.children[character] = next_node

			# Move one node deeper into the tree (current_node now contains the character -> we need to add entire word)
			current_node = next_node
			current_depth += 1

		# If the current node already has a word return?
		if current_node.word is not None:
			#print ("you have already printed " + word)
			return

		# Set the word (output) of the current node to be the input word and increment the size of the Trie
		current_node.word = word
		self.size += 1


	def lookup(self,word):
		current_node = self.root
		for character in word:
			next_node = current_node.children.get(character)
			if not next_node:
				return False

			current_node = next_node

		return True


	def is_root(self, node):
		return node.character is None


	def node_has_child(self, node, character):
		return node.children.get(character) is not None


	def get_AC_suffix_link(self, node):
		searcher = node.parent.ACsuffix_link
		while (not self.is_root(searcher)) and (not self.node_has_child(searcher, node.character)):
			searcher = searcher.ACsuffix_link
			if not searcher:
				import pdb; pdb.set_trace()

		if (self.node_has_child(searcher, node.character)):
			return searcher.children[node.character]
		else:
			if (not self.is_root(searcher)):
				print ("ERROR: Incorrect looping in suffix links")
			return searcher


class CWSearch(Trie):
	def create_node(self, character, depth, parent):
		return CWNode(character, depth, parent)


	def __init__(self):
		""" Initializes CW Search class
		"""
		# Intitialize the following:
		# * name
		# * complexity
		# * preprocess_t_ms = [] # Preprocessing time in ms
		# * search_t_ms = [] # Search time in ms
		# * sorted_time_cols = [] # Sorted columns of times of individual runs and total run times
		AutomatonSearch.__init__(self, "CW", "O(nm)")


	def add_word(self, word):
		# Reverse the word (e.g "word" -> "drow")
		word = word[::-1]
		# Add the word to the Trie
		super().add_word(word)

		pos = 1

		#Initialize character table
		for character in word:
			# Find the character in the lookup table
			min_char_depth = self.char_lookup_table.get(character)
			
			# If the character doesn't exist in the lookup table or it is bigger than the pos 
			# -> set pos to the position of the character in the lookup table (using character as the index)
			if (min_char_depth is None) or (min_char_depth > pos):
				self.char_lookup_table[character] = pos
			# Increment pos - keeping track of where in the word we are (disregarding unique chars)
			pos += 1

		# If mind_depth of CW doesn't exist, set it to be the length of the word
		if self.min_depth is None:
			self.min_depth = len(word)
		elif len(word) < self.min_depth:
			self.min_depth = len(word)


	def lookup(self, word):
		word = word[::-1]
		super().lookup(word)


	def initialize_shift_values(self):
		bfs_queue = deque()
		self.root.shift1 = 1
		self.root.shift2 = self.min_depth

		for key in self.root.children:
			bfs_queue.append(self.root.children[key])

		while (len(bfs_queue) > 0):
			current_node = bfs_queue.popleft()
			# set shift1
			if current_node.CWsuffix_link is None:
				current_node.shift1 = self.min_depth
			else:
				current_node.shift1 = current_node.min_difference_s1

			#set shift2
			if current_node.CWoutput_link is None:
				current_node.shift2 = current_node.parent.shift2
			else:
				current_node.shift2 = current_node.min_difference_s2

			for key in current_node.children:
				bfs_queue.append(current_node.children[key])


	def create_failure_links(self):
		bfs_queue = deque()

		# First, set suffix links for first children to root
		for key in self.root.children:
			child = self.root.children[key]
			child.ACsuffix_link = self.root

			for key2 in child.children:
				grandchild = child.children[key2]
				bfs_queue.append(grandchild)

		while (len(bfs_queue) > 0):
			current_node = bfs_queue.popleft()
			for key in current_node.children:
				child = current_node.children[key]
				bfs_queue.append(child)

			# Set AC nodes first
			AC_suffix_node = self.get_AC_suffix_link(current_node)
			current_node.ACsuffix_link = AC_suffix_node
			suffix_is_word = current_node.ACsuffix_link.word is not None
			current_node.ACoutput_link = current_node.ACsuffix_link if suffix_is_word else current_node.ACsuffix_link.ACoutput_link
			if current_node.ACoutput_link is not None:
				pass

			# Set reverse suffix links and output links
			is_set2 = current_node.word is not None
			if AC_suffix_node.min_difference_s1 == -1 or AC_suffix_node.min_difference_s1 > current_node.depth - AC_suffix_node.depth:
				AC_suffix_node.min_difference_s1 = current_node.depth - AC_suffix_node.depth
				AC_suffix_node.CWsuffix_link = current_node
			if is_set2:
				if AC_suffix_node.min_difference_s2 == -1 or AC_suffix_node.min_difference_s2 > current_node.depth - AC_suffix_node.depth:
					AC_suffix_node.min_difference_s2 = current_node.depth - AC_suffix_node.depth
					AC_suffix_node.CWoutput_link = current_node

		self.initialize_shift_values()


	def char_func(self, character):
		min_depth = self.char_lookup_table.get(character)
		if min_depth is None:
			min_depth = self.min_depth + 1

		return min_depth


	def shift_func(self, node, j):
		max_of_s1_and_char = 0
		if node.character is None:
			max_of_s1_and_char = node.shift1
		else:
			max_of_s1_and_char = max(self.char_func(node.character) - j - 1, node.shift1)
		return min(max_of_s1_and_char, node.shift2)


	# preprocess
	def preprocess(self, keywords):
		"""Create the Trie for the CW algorithm
		@param keywords: list of keywords
		"""
		if isinstance(keywords, str) or isinstance(keywords, int):
			keywords = [keywords]

		start_t = datetime.now()

		# Trie setup
		Trie.__init__(self)
		self.min_depth = None
		self.char_lookup_table = {}

		for keyword in keywords:
			self.add_word(keyword)
		self.create_failure_links()

		end_t = datetime.now()
		preprocess_t_ms = self.process_time_ms(start_t, end_t)
		return keywords, preprocess_t_ms


	# pure_search
	def pure_search(self, n, text, index_list):
		""" returns list of indexes if the text contains any keywords in trie, format: (start_idx, keyword) """
		i = self.min_depth - 1

		while (i < n):
			# Scan Phase
			v = self.root
			j = 0
			char_to_find = text[i - j]
			# Find child of root that has the character we are currently looking at in the text
			while self.node_has_child(v, char_to_find) and (i - j >= 0):
				# We have the child with the character
				v = v.children[char_to_find]

				# Increment the index tracking the keyword
				j += 1

				# If the node is an output node (its word exists)
				# -> append the beginning index of the word and the reversed word (we scan word from right to left)
				#    -> i.e. words are stored with their chars in reverse order
				if (v.word is not None):
					index_list.append((i - j + 1, v.word[::-1]))

				# Increment the char to find
				char_to_find = text[i-j]

			# If index of word has overflown index of text => reset
			if (j > i):
				j = i

			# Shift the index looking at the text according to max. possible shift
			i += self.shift_func(v, j)

		return index_list
from collections import deque

# Custom local file imports
from Automaton_base_class import AutomatonSearch
from Automaton_base_class import datetime

class ACSearch(AutomatonSearch):
    
    def __init__(self, lowercase=False):
        """ Initializes AC Search class
        :param lowercase: convert all strings to lower case
        """
        # Intitialize the following:
        # * name
        # * complexity
        # * preprocess_t_ms = [] # Preprocessing time in ms
		# * search_t_ms = [] # Search time in ms
		# * sorted_time_cols = [] # Sorted columns of times of individual runs and total run times
        super().__init__("AC", "O(n + m + z)")
        self.lowercase = lowercase


    def add_keywords(self, keywords):
        """ add all keywords in list of keywords """
        for keyword in keywords:
            self.add_keyword(keyword, None)


    def add_keywords_and_values(self, kvs):
        """ add all keywords and values in list of (k,v) """
        for k,v in kvs:
            self.add_keyword(k,v)


    def find_next_state(self, current_state, value):
        for node in self.AdjList[current_state]["next_states"]:
            if self.AdjList[node]["value"] == value:
                return node
        return None


    def add_keyword(self, keyword, value):
        """ add a keyword to the trie and mark output at the last node """
        current_state = 0
        j = 0
        if self.lowercase: keyword = keyword.lower()
        # Get the child of the root (id = 0) that contains the 0th character of the keyword 
        child = self.find_next_state(current_state, keyword[j])

        # If the 0th character of the keyword is already in the tree (a child of the root with the character is not None)
        # While the child exists we will traverse down the trie (tree) and create nodes of the tree with the keyword's characters
        while child != None:
            current_state = child
            # Increment the index for the keyword
            j = j + 1
            # If the keyword hasn't been processed entirely find the next child node. Otherwise break the while cycle as we have processed everything
            if j < len(keyword):
                child = self.find_next_state(current_state, keyword[j])
            else:
                break
        # If the keyword doesn't yet exist in the trie (child of root with 0th char of keyword was None)
        # -> Here, either there is no child of the root that has the 0th char of the word,
        #    or current_state is the output node for this word, 
        #    or the word isn't fully contianed in the tree -> this for loop is for that (we add the remaining 
        #     part of the word that is not found in the tree)
        # Iterate from the j-th index of the keyword (above cycle will end if we find that traversal
        #  in the tree doesn't contain part of the word beginning with index j of the keyword)
        # -> Iterate from j to the end of the keyword (to add the remaining part of the keyword)
        for i in range(j, len(keyword)):
            # Create a new node for the character that was not found in the tree
            node = {'value':keyword[i],'next_states':[],'fail_state':0,'output':[]}
            # Add it to the list of nodes
            self.AdjList.append(node)
            # Add the node as a child to the current parent (adding its index in the list)
            self.AdjList[current_state]["next_states"].append(len(self.AdjList) - 1)
            # Make the just added child node to be the current node
            current_state = len(self.AdjList) - 1
        # To the current node's output (last of the traversal for this specific keyword) add the keyword 
        #  (if we arrive at this node, we know that we have found this keyword in the text)
        self.AdjList[current_state]["output"].append((keyword,value))


    def set_fail_transitions(self):
        q = deque()
        child = 0
        # Add each child of the root node to the queue and make their fail states be the root node 
        for node in self.AdjList[0]["next_states"]:
            q.append(node)
            self.AdjList[node]["fail_state"] = 0
        # While there are nodes in the queue
        while q:
            # Process each child of the root (remove them from the queue)
            r = q.popleft()

            # For each child of the popped node we will set failure states
            for child in self.AdjList[r]["next_states"]:
                # Add the child to the queue
                q.append(child)
                # Get the fail state of the popped node (initially fail state is root node)
                state = self.AdjList[r]["fail_state"]

                # Initially the potential parent of the fail state of "child", "state" will be the next longest proper suffix, 
                # which is marked by "r"'s fail state. If there is no transition from "r"'s fail state to a node with the same 
                # value as "child", then we go to the next longest proper suffix, which is the fail state of "r"'s fail state, 
                # and so on, until we find one which works, or we are at the root. We set "child"'s fail state to be this fail state.
                while self.find_next_state(state, self.AdjList[child]["value"]) == None and state != 0:
                    state = self.AdjList[state]["fail_state"]
                # We have found the next node that has the same value as our current state and it has a fail state

                self.AdjList[child]["fail_state"] = self.find_next_state(state, self.AdjList[child]["value"])

                # If the fail state we have arrived at does not exist => set the fail state to be root
                if self.AdjList[child]["fail_state"] is None:
                    self.AdjList[child]["fail_state"] = 0

                # Set the child's output (match is found) to be the output words of the child + the output words of the fail state node
                self.AdjList[child]["output"] = self.AdjList[child]["output"] + \
                                                self.AdjList[self.AdjList[child]["fail_state"]]["output"]


    def preprocess(self, keywords):
        """ creates a trie of keywords, then sets fail transitions
        :param keywords: trie of keywords
        """
        if isinstance(keywords, str) or isinstance(keywords, int):
            keywords = [keywords]
            
        start_t = datetime.now()

        # initalize the root of the trie
        self.AdjList = list()
        self.AdjList.append({'value':'', 'next_states':[],'fail_state':0,'output':[]})

        if isinstance(keywords[0], tuple):
            self.add_keywords_and_values(keywords)
        else:
            self.add_keywords(keywords)
        self.set_fail_transitions()

        end_t = datetime.now()

        preprocess_t_ms = self.process_time_ms(start_t, end_t)
        return keywords, preprocess_t_ms


    def pure_search(self, n, text, index_list):
        """ returns list of indexes if the text contains any keywords in trie, format: (start_idx, keyword, value) """

        # Search for keyword with lowercase
        if self.lowercase: text = text.lower()

        # Begin at the root
        current_state = 0

        # For each index of a character in the text
        for i in range(0, n):
            # From the current state (initially root), find the characher. 
            # While the value is not found and the current state is not the root
            while self.find_next_state(current_state, text[i]) is None and current_state != 0:
                # Keep going by fail states
                current_state = self.AdjList[current_state]["fail_state"]
            # The loop stopped either if: 1) We found the node with the character, or 2) We have arrived at the root.
            # The the next state that we found.
            current_state = self.find_next_state(current_state, text[i])

            # If the found node doesn't exist (word doesn't exist in the Trie) => set the current state to be the root of the trie.
            if current_state is None:
                current_state = 0
            else: # If we have found the node, then take the key and value of the output node and add it to the list of found keywords
                for k,v in self.AdjList[current_state]["output"]:
                    index_list.append((i-len(k) + 1, k, v))

        return index_list
from Automaton_base_class import AutomatonSearch
from Automaton_base_class import datetime, READ_FILE_BY_ROW

class DKASearch(AutomatonSearch):

    # https://www.geeksforgeeks.org/ord-function-python/
    #NO_OF_CHARS = 65536
    NO_OF_CHARS = 256

    def __init__(self):
        super().__init__("DKA", "O(n)")

    def init_search(self, text, keywords):
        match_list = []
        n = len(text)

        if isinstance(keywords, str) or isinstance(keywords, int):
            keywords = [keywords]

        # Remove duplicates from keywords
        keywords = list(dict.fromkeys(keywords))

        num_words = len(keywords)
        m = [0]*num_words
        state = [0]*num_words

        if READ_FILE_BY_ROW == True:
            for _ in range(0, n):
                match_list.append([])
        print(len(match_list))

        for i in range(0, num_words):
            m[i] = len(keywords[i])

        return n, m, keywords, num_words, state, match_list

    def getNextState(self, pat, m, state, x):
        """    calculate the next state 
        """

        if state < m and x == ord(pat[state]):
            return state + 1

        i = 0

        for ns in range(state, 0, -1):
            if ord(pat[ns - 1]) == x:
                while (i < ns - 1):
                    if pat[i] != pat[state - ns + 1 + i]:
                        break
                    i += 1
                if i == ns - 1:
                    return ns
        return 0
    
    def computeTF(self, word, m, TF, j):
        for state in range(0, m + 1):
            for x in range(0, self.NO_OF_CHARS):
                TF[j][state][x] = self.getNextState(word, m, state, x)

    def preprocess(self, keywords, num_words, m):
        '''
        This function builds the TF table which 
        represents Finite Automata for a given pattern 
        '''

        start_t = datetime.now()
        
        TF = [[[0 for i in range(self.NO_OF_CHARS)] for _ in range(0, m[word_idx] + 1)] for word_idx in range(0, num_words)]

        for k in range(0, len(keywords)):
            self.computeTF(keywords[k], m[k], TF, k)

        end_t = datetime.now()
        preprocess_t_ms = self.process_time_ms(start_t, end_t)
        return TF, preprocess_t_ms


    def pure_search(self, n, m, text, keywords, num_words, state, TF, index_list):
        '''
        Returns array of all occurrences of patterns in text 
        '''

        for i in range(0, n):
            for j in range(0, num_words):
                state[j] = TF[j][state[j]][ord(text[i])]
                if state[j] == m[j]:
                    # TODO: This must append a tuple to the index_list with the following format: (start_idx, keyword)
                    index_list.append((i - m[j] + 1, keywords[j]))
    
        return index_list

    def search(self, text, keywords):
        # Print the start of a given algorithm output in the console
        print("===START " + self.get_name())

        # Initialize starting variables
        n, m, keywords, num_words, state, match_list = self.init_search(text, keywords)

        # Preprocess the pattern
        TF, preprocess_t_ms = self.preprocess(keywords, num_words, m)

        start_t = datetime.now()
        print("Search start: \t" + str(start_t))

        # Reading the input as and entire string or row by row.
        # This allows the output to show in which row and on which index of that row was a match found
        if READ_FILE_BY_ROW == False:
            match_list = self.pure_search(n, m, text, keywords, num_words, state, TF, match_list)
        else:
            row_index = 0
            for row in text:
                n = len(row)
                
                match_list[row_index] = self.pure_search(n, m, row, keywords, num_words, state, TF, match_list[row_index])
                row_index += 1
        
        end_t = datetime.now()
        print("Search finish: \t" + str(end_t))

        # print summarizing information about the matches of the pattern
        self.print_search_summary(keywords, match_list)

        search_t_ms = self.process_time_ms(start_t, end_t)
        print("\nTotal runtime: " + str(search_t_ms) + "ms")
        print("===FINISH " + self.get_name() + "\n")

        return preprocess_t_ms, search_t_ms
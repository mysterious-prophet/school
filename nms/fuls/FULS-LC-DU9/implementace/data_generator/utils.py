def utf8len(s):
	#https://stackoverflow.com/a/55201398/7941877
    return len(s.encode('utf-8'))


def get_byte_size(string):
	return (len(string) if isinstance(string, bytes) else utf8len(string))


def list_to_str(string):
	return ";".join([str(elem) for elem in string])
import yaml # For settings import
settings = yaml.safe_load(open("settings/settings.yml"))

# Custom local file imports
from data_generator.utils import get_byte_size



class Compress():
	"Base class for all compression algorithms"
	
	def __init__(self, name, encoded_text_in_bits = True):
		self.name = name
		self.encoded_text_in_bits = encoded_text_in_bits


	def get_name(self):
		return self.name


	def print_text_bit_length(self, text):
		print("\nlength is %i bits" % (len(text)*8))


	def get_compression_ratio(self, text, encoded_text, encoded_text_in_bits = None):
		encoded_text_in_bits = self.encoded_text_in_bits if encoded_text_in_bits == None else encoded_text_in_bits

		if encoded_text_in_bits:
			c_rate = len(encoded_text) / (get_byte_size(text)*8.0)
		else:
			c_rate = get_byte_size(encoded_text) / get_byte_size(text) * 1.0
		return round(c_rate*100, settings["DEC_ACCURACY"])
import yaml # For settings import
settings = yaml.safe_load(open("settings/settings.yml"))



class Benchmark:
	"Basic class for a benchmark"
	
	def __init__(self, name):
		self.name = name


	def get_name(self):
		return self.name


	def process_time_ms(self, start_t, end_t):
		"Return time in ms between start_t and end_t"
		t = end_t - start_t
		t_ms = round(t.total_seconds()*1000, settings["DEC_ACCURACY"]) # secs to ms rounded to DEC_ACCURACY decimal places
		return t_ms
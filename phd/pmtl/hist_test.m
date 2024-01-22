data_formats = '%D%f';
data = readtable('pocet_pacientu.csv','Format', data_formats);

h = histogram("Categories", categorical(data.Date), "BinCounts", data.Patients);

import json

jsFile = open("metro.json")
js = jsFile.readline()

data = json.loads(js)

lines = open("lines.tsv", "w")
lines.write("LineID\tName\n")

stations = open("stations.tsv", "w")
stations.write("StationID\tLineID\tName\n")

transfers = open("transfers.tsv", "w")
transfers.write("StartsStationID\tEndsStationID\n")

for l in data["lines"]:
    lineId = l
    name = data["lines"][l]["name"]
    lines.write("%s\t\"%s\"\n" % (lineId, name))

for s in data["stations"]:
    stationId = s
    name = data["stations"][s]["name"]
    lineId = data["stations"][s]["lineId"]
    stations.write("%s\t%s\t\"%s\"\n" % (stationId, lineId, name))

for t in data["transfers"]:
    ids = list(data["transfers"][t]["stationIds"])
    for i in range(len(ids)):
        for j in range(len(ids)):
            if i != j:
                transfers.write("%d\t%d\n" % (ids[i], ids[j]))

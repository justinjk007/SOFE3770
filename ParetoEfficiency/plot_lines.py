import csv
import sys
import matplotlib.pyplot as plt

fig = plt.figure()
ax = fig.add_subplot(111)

def parse(file_name):
    "Parses the data sets from the csv file we are given to work with"
    try:
        file = open(file_name)
    except IOError:
        print "Failed to open the data file"
        sys.exit()
    rawFile = csv.reader(file)    # Reading the csv file into a raw form
    rawData = list(rawFile)       # Converting the raw data into list from.
    file.close()
    return rawData

def toXandY(unorderedData):
    "This method converts seperates x and y co-ordinates for plotting"
    orderedData = []
    orderedData.append([])        # Add a new sublist every time
    orderedData.append([])        # Add a new sublist every time
    listSize = len(unorderedData)
    for x in range(0, listSize):
        orderedData[0].append(unorderedData[x][0])  # Seperates the x-cords
    for y in range(0, listSize):
        orderedData[1].append(unorderedData[y][1])  # Seperates the y-cords
    return orderedData

def main():
    newData = []
    f_line_x = []
    f_line_y = []
    file_name = "data.csv"
    data = parse(file_name)   # Calling the parse funtion we made
    labels = data.pop(0)            # Necessary evil
    frontier_size = int(data.pop(0)[0])
    list_size = len(data)
    for i in range(0, list_size):    # Converting the string list to float
        newData.append([])          # Add a new sublsit every time
        for j in range(0, 2):       # Append converted data to the new list
            newData[i].append(float(data[i][j]))
    DataXandY = toXandY(newData)     # DataXandY -> [[Xs][Ys]]
    i = 0
    while i < frontier_size:
        i+=1
        f_line_x.append(DataXandY[0].pop(0))
        f_line_y.append(DataXandY[1].pop(0))

    plt.xlabel(labels[0])
    plt.ylabel(labels[1])
    plt.title("Pareto dominance")
    plt.plot(DataXandY[0], DataXandY[1], "o", color="g") # Plot all points
    plt.plot(f_line_x, f_line_y, "-o", color="r") # Plot frontier line

    plt.gca().set_aspect('equal', adjustable='box')
    plt.show()

if __name__ == "__main__":
    main()

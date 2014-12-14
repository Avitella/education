import mysql.connector

import random
import time

def strTimeProp(start, end, prop):
    format = '%Y-%m-%d %H:%M'
    stime = time.mktime(time.strptime(start, format))
    etime = time.mktime(time.strptime(end, format))
    ptime = stime + prop * (etime - stime)
    return time.strftime(format, time.localtime(ptime))


def randomDate(start, end):
    return strTimeProp(start, end, random.random())

ITERATIONS = 1000

cnx = mysql.connector.connect(user="root", password="", database="metro")

cursor = cnx.cursor()

for iterations in range(ITERATIONS):
    cursor.execute("""
        insert into TurnstileRecord (MetroStationID, Status, Date) values (%s, %s, \"%s:00\")
    """ % (str(random.randrange(1, 197)), str(random.randrange(1, 3)), randomDate("2014-1-1 1:30", "2014-12-10 4:50")))

cnx.commit()

cnx.close()

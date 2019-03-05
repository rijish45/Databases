
#Rijish Ganguly
#CS516
#rg239


import xml.sax
import psycopg2


def quoted(key):
    return "\'" + key.replace('\'', '\'\'') + "\'"


class Dblp:

    def __init__(self):
        try:
            self.conn = psycopg2.connect("dbname=dblp user=rijishganguly password=HAdouken1*")
            self.cur = self.conn.cursor()
        except psycopg2.Error as e:
            print("Couldn't connect with the Database")

    def add_author(self, pubkey, author):
        sql = "insert into authorship(pubkey,author)"
        sql += "values(" + quoted(pubkey) + "," + quoted(author) + ")" + "on conflict do nothing"
        self.execute_sql(sql)

    def add_article(self, pubkey, title, journal, year):
        sql = "insert into article(pubkey,title, journal, year)"
        sql += "values(" + quoted(pubkey) + "," + quoted(title) + "," + quoted(
            journal) + "," + year + ")" + "on conflict do nothing"
        self.execute_sql(sql)

    def add_inproceedings(self, pubkey, title, booktitle, year):
        sql = "insert into inproceedings(pubkey,title,booktitle, year)"
        sql += "values(" + quoted(pubkey) + "," + quoted(title) + "," + quoted(
            booktitle) + "," + year + ")" + "on conflict do nothing"
        self.execute_sql(sql)

    def execute_sql(self, sql_command):
        self.cur.execute(sql_command)
        self.conn.commit()

    def create_tables(self):
        """ create tables in the PostgreSQL database"""
        self.cur.execute("CREATE TABLE article (pubkey TEXT PRIMARY KEY, title TEXT, journal TEXT, year INT);")
        self.cur.execute("CREATE TABLE inproceedings (pubkey TEXT PRIMARY KEY, title TEXT, booktitle TEXT, year INT);")
        self.cur.execute("CREATE TABLE authorship (pubkey TEXT, author TEXT, PRIMARY KEY(pubkey, author)) ;")
        self.conn.commit()


Database = Dblp()
Database.create_tables()


class XMLHandler(xml.sax.ContentHandler):
    def __init__(self):
        self.CurrentData = ""
        self.title = ""
        self.journal = ""
        self.year = None
        self.booktitle = ""
        self.author = ""
        self.pubkey = ""

    def startElement(self, tag, attributes):
        self.CurrentData = tag
        if tag == "article" or tag == "inproceedings":
            key = attributes["key"]
            self.pubkey = key
        elif tag == "title":
            self.title = ""
        elif tag == "author":
            self.author = ""
        elif tag == "booktitle":
            self.booktitle = ""
        elif tag == "journal":
            self.journal = ""
        elif tag == "year":
            self.year = ""

    # Call when an elements ends
    def endElement(self, tag):
        if self.pubkey != "":
            if self.year == "":
                year = "null"
            else:
                year = self.year
            if tag == "author":
                Database.add_author(self.pubkey, self.author)
            elif tag == "inproceedings":
                Database.add_inproceedings(self.pubkey, self.title, self.booktitle, year)
                self.pubkey = ""
            elif tag == "article":
                Database.add_article(self.pubkey, self.title, self.journal, year)
                self.pubkey = ""
            self.CurrentData = ""

    # Call when a character is read
    def characters(self, content):
        if self.CurrentData == "title":
            self.title += content
        elif self.CurrentData == "year":
            self.year += content
        elif self.CurrentData == "journal":
            self.journal += content
        elif self.CurrentData == "booktitle":
            self.booktitle += content
        elif self.CurrentData == "author":
            self.author += content
        elif self.CurrentData == "year":
            self.year += content

# create an XMLReader
parser = xml.sax.make_parser()
parser.setFeature(xml.sax.handler.feature_namespaces, 0)

# override the default ContextHandler
Handler = XMLHandler()
parser.setContentHandler(Handler)
parser.parse("dblp-2018-08-01.xml")

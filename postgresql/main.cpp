#include <iostream>
#include <pqxx/pqxx>
#include <string>
#include "exerciser.h"

using namespace std;
using namespace pqxx;



void drop_existing_tables(connection * C){


  string sql = "DROP TABLE IF EXISTS PLAYER, TEAM, STATE, COLOR;";
  work W(*C);
  W.exec(sql);
  W.commit();
  

};


void add_player(connection * C){

  string sql = "CREATE TABLE PLAYER("  \
      "PLAYER_ID    SERIAL PRIMARY KEY     NOT NULL," \
      "TEAM_ID      INT                    NOT NULL," \
      "UNIFORM_NUM  INT                    NOT NULL," \
      "FIRST_NAME   TEXT                   NOT NULL," \
      "LAST_NAME    TEXT                   NOT NULL," \
      "MPG          INT                    NOT NULL," \
      "PPG          INT                    NOT NULL," \
      "RPG          INT                    NOT NULL," \
      "APG          INT                    NOT NULL," \
      "SPG          REAL                   NOT NULL," \
      "BPG          REAL                   NOT NULL);";  
         

    work W(*C);
    W.exec(sql);
    W.commit();
    cout << "Table Player has been created" << endl;
   
};



void add_team (connection * C){

 string sql = "CREATE TABLE TEAM("  \
      "TEAM_ID      SERIAL PRIMARY KEY     NOT NULL," \
      "NAME         TEXT                   NOT NULL," \
      "STATE_ID     INT                    NOT NULL," \
      "COLOR_ID     INT                    NOT NULL," \
      "WINS         INT                    NOT NULL," \
      "LOSSES       INT                    NOT NULL);";

    work W(*C);
    W.exec(sql);
    W.commit();
    cout << "Table Team has been created" << endl;
 

};
//void add_state(Connection * C){}
//void add_color(Connection * C){};




int main (int argc, char *argv[]) 
{

  //Allocate & initialize a Postgres connection object
  connection *C;

  try{
    //Establish a connection to the database
    //Parameters: database name, user name, user password
    C = new connection("dbname=ACC_BBALL user=postgres password=passw0rd");
    if (C->is_open()) {
      cout << "Opened database successfully: " << C->dbname() << endl;
    } else {
      cout << "Can't open database" << endl;
      return 1;
    }
  } catch (const std::exception &e){
    cerr << e.what() << std::endl;
    return 1;
  }


  //TODO: create PLAYER, TEAM, STATE, and COLOR tables in the ACC_BBALL database
  //      load each table with rows from the provided source txt files

  drop_existing_tables(C);
  add_player(C);
  add_team(C);
  exercise(C);


  //Close database connection
  C->disconnect();

  return 0;
}



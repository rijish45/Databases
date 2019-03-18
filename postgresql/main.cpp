#include <iostream>
#include <pqxx/pqxx>
#include <string>
#include <fstream>
#include "exerciser.h"
#include "query_funcs.h"

using namespace std;
using namespace pqxx;

  void load_players ( string filename, connection * C){
    ifstream file;
    file.open(filename);
    if(!file.good()){
      cout << "File not found." << endl;
      return;
    }

    else{

      string input_line;
      while(getline(file, input_line)){

	int id;
	int team_id;
	int uniform_num;
	int state_id;
	string first_name;
	string last_name;
	int mpg, ppg, rpg, apg;
	float spg, bpg;

	
	istringstream ss(input_line);
	if(input_line.empty()){
	  ;
	}
	else{
	  if( !(ss >> id >> team_id >> uniform_num >> first_name >> last_name >> mpg >> ppg >> rpg >> apg >> spg >> bpg)){
	    break;
	  }
	  else{

	    ss >> id >> team_id >> uniform_num >> first_name >> last_name >> mpg >> ppg >> rpg >> apg >> spg >> bpg;
	    // cout << first_name << endl;
	    // cout << last_name << endl;

	    size_t found = first_name.find("'");
	    if(found != string::npos){
	      first_name.replace(found,1,"''");
	     }
	    found = last_name.find("'");
	    if(found != string::npos){
	      last_name.replace(found,1, "''");
	    }

	    // cout << first_name << endl;
	    // cout << last_name << endl;
	    
	    add_player(C, team_id, uniform_num, first_name, last_name, mpg, ppg, rpg, apg, spg, bpg);
	 }


	}
	
      }

  }
    file.close();

  }



void load_teams( string filename, connection * C){

  ifstream file;
    file.open(filename);
    if(!file.good()){
      cout << "File not found." << endl;
      return;
    }

    else{

      string input_line;
      while(getline(file, input_line)){

	int team_id;
	string team_name;
	int losses;
	int wins;
	int state_id;
	int color_id;
       

	istringstream ss(input_line);
	if(input_line.empty()){
	  ;
	}
	else{
	  if( !(ss >> team_id >> team_name >> state_id >> color_id >> wins >> losses)){
	    break;
	  }
	  else{
	    add_team(C, team_name, state_id, color_id, wins, losses);
	 }


	}
	
      }

  }
    file.close();

}




void load_state(string filename, connection * C) {

 ifstream file;
    file.open(filename);
    if(!file.good()){
      cout << "File not found." << endl;
      return;
    }

    else{

      string input_line;
      while(getline(file, input_line)){

	int state_id;
	string state_name;
       

	istringstream ss(input_line);
	if(input_line.empty()){
	  ;
	}
	else{
	  if(!(ss >> state_id >> state_name)){
	    break;
	  }
	  else{
	    add_state(C, state_name);
	 }


	}
	
      }

  }
    file.close();
}


void drop_existing_tables(connection * C){


  string sql = "DROP TABLE IF EXISTS PLAYER, TEAM, STATE, COLOR;";
  work W(*C);
  W.exec(sql);
  W.commit();
  

}

void load_color(string filename, connection * C){


ifstream file;
    file.open(filename);
    if(!file.good()){
      cout << "File not found." << endl;
      return;
    }

    else{

      string input_line;
      while(getline(file, input_line)){

	int color_id;
	string color_name;
       

	istringstream ss(input_line);
	if(input_line.empty()){
	  ;
	}
	else{
	  if(!(ss >> color_id >> color_name)){
	    break;
	  }
	  else{
	    add_color(C, color_name);
	 }


	}
	
      }

  }
 
    file.close();
}





void add_player(connection * C){

  string sql = "CREATE TABLE PLAYER("  
      "PLAYER_ID    SERIAL PRIMARY KEY     NOT NULL," 
      "TEAM_ID      INT                    NOT NULL," 
      "UNIFORM_NUM  INT                    NOT NULL," 
      "FIRST_NAME   TEXT                   NOT NULL," 
      "LAST_NAME    TEXT                   NOT NULL," 
      "MPG          INT                    NOT NULL," 
      "PPG          INT                    NOT NULL," 
      "RPG          INT                    NOT NULL," 
      "APG          INT                    NOT NULL," 
      "SPG          REAL                   NOT NULL," 
      "BPG          REAL                   NOT NULL);";  
         

    work W(*C);
    W.exec(sql);
    W.commit();
    cout << "Table Player has been created." << endl;
   
}



void add_team (connection * C){

 string sql = "CREATE TABLE TEAM("  
      "TEAM_ID      SERIAL PRIMARY KEY     NOT NULL," 
      "NAME         TEXT                   NOT NULL," 
      "STATE_ID     INT                    NOT NULL," 
      "COLOR_ID     INT                    NOT NULL," 
      "WINS         INT                    NOT NULL," 
      "LOSSES       INT                    NOT NULL);";

    work W(*C);
    W.exec(sql);
    W.commit();
    cout << "Table Team has been created." << endl;
 

}


void add_state(connection * C){


  string sql = "CREATE TABLE STATE(" 
                "STATE_ID	SERIAL PRIMARY KEY NOT NULL," 
	        "NAME		TEXT               NOT NULL);";

  work W(*C);
  W.exec(sql);
  W.commit();
  cout << "Table State has been created." << endl;

}



void add_color(connection * C){

string sql = "CREATE TABLE COLOR("
	     "COLOR_ID	SERIAL PRIMARY KEY NOT NULL,"
	     "NAME	TEXT	           NOT NULL);";

 work W(*C);
 W.exec(sql);
 W.commit();
 cout << "Table Color has been created." << endl;
  
}




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

  drop_existing_tables(C);
  add_player(C);
  add_team(C);
  add_state(C);
  add_color(C);
  
  

 // load each table with rows from the provided source txt files

  string filename  = "player.txt";
  load_players(filename, C);  
  filename = "team.txt";
  load_teams(filename, C);
  filename = "state.txt";
  load_state(filename, C);
  filename = "color.txt";
  load_color(filename, C);

  
  exercise(C);


  //Close database connection
  C->disconnect();

  return 0;
}



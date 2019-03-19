#include "query_funcs.h"


void add_player(connection *C, int team_id, int jersey_num, string first_name, string last_name,
                int mpg, int ppg, int rpg, int apg, double spg, double bpg)
{

  ostringstream ss;
  work W(*C);
  string sql_temp = "INSERT INTO PLAYER (TEAM_ID, UNIFORM_NUM, FIRST_NAME, LAST_NAME, MPG, PPG, RPG, APG, SPG, BPG)";
  ss << "VALUES (" << team_id << ", " << jersey_num << ", '" << first_name << "', '" << last_name << "', " << mpg << ", " << ppg << ", " << rpg << ", " << apg << ", " << spg << ", " << bpg << " );";
  string sql = sql_temp + ss.str();

  W.exec(sql);
  W.commit();
  
  
  
}


void add_team(connection *C, string name, int state_id, int color_id, int wins, int losses)
{
  ostringstream ss;
  work W(*C);
  string sql_temp = "INSERT INTO TEAM (NAME, STATE_ID, COLOR_ID, WINS, LOSSES)";
  ss << "VALUES ('" <<  name  << "', " << state_id << ", " <<  color_id  << ", " << wins  << ", "<< losses << ");";
  string sql = sql_temp + ss.str();
  W.exec(sql);
  W.commit();
  
}


void add_state(connection *C, string name)
{

  ostringstream ss;
  work W(*C);
  string sql_temp = "INSERT INTO STATE( NAME)";
  ss << "VALUES ('" << name << "');";
  string sql = sql_temp + ss.str();
  W.exec(sql);
  W.commit();
}


void add_color(connection *C, string name)
{

  ostringstream ss;
  work W(*C);
  string sql_temp = "INSERT INTO COLOR( NAME)";
  ss << "VALUES ('" << name << "');";
  string sql = sql_temp + ss.str();
  W.exec(sql);
  W.commit();
  
}


void query1(connection *C,
	    int use_mpg, int min_mpg, int max_mpg,
            int use_ppg, int min_ppg, int max_ppg,
            int use_rpg, int min_rpg, int max_rpg,
            int use_apg, int min_apg, int max_apg,
            int use_spg, double min_spg, double max_spg,
            int use_bpg, double min_bpg, double max_bpg
            )
{
  
  nontransaction N(*C);
  bool condition = true;
  ostringstream sql;
  sql << "SELECT * FROM PLAYER AS P ";

  if(use_mpg){

    sql << "WHERE P.MPG BETWEEN " << min_mpg << " AND " << max_mpg << "  ";
    condition = false;
    
  }
  if(use_ppg){

    if(condition){
      sql << " WHERE ";
    }
    else
      sql << " AND ";

    sql << " P.PPG BETWEEN " << min_ppg << " AND " << max_ppg << " ";
    condition = false;
    
  }
   if(use_rpg){

    if(condition){
      sql << " WHERE ";
    }
    else
      sql << " AND ";

    sql << " P.RPG BETWEEN " << min_rpg << " AND " << max_rpg << " ";
    condition = false;
    
  }
   if(use_apg){

    if(condition){
      sql << " WHERE ";
    }
    else
      sql << " AND ";

    sql << " P.APG BETWEEN " << min_ppg << " AND " << max_ppg << " ";
    condition = false;
    
  }
   if(use_spg){

    if(condition){
      sql << " WHERE ";
    }
    else
      sql << " AND ";

    sql << " P.SPG BETWEEN " << min_ppg << " AND " << max_ppg << " ";
    condition = false;
    
  }
   if(use_bpg){

    if(condition){
      sql << " WHERE ";
    }
    else
      sql << " AND ";

    sql << " P.BPG BETWEEN " << min_ppg << " AND " << max_ppg << " ";
    condition = false;
    
  }
 
   sql << " ; ";
   result output = N.exec(sql.str());

   cout << "PLAYER_ID TEAM_ID UNIFORM_NUM FIRST_NAME LAST_NAME MPG PPG RPG APG SPG BPG" << endl;
   result::const_iterator it;
   for (it = output.begin(); it != output.end(); it++){

     cout << it[0].as<int>() << " ";
     cout << it[1].as<int>() << " ";
     cout << it[2].as<int>() << " ";
     cout << it[3].as<string>() << " ";
     cout << it[4].as<string>() << " ";
     cout << it[5].as<int>() << " ";
     cout << it[6].as<int>() << " ";
     cout << it[7].as<int>() << " ";
     cout << it[8].as<int>() << " ";
     cout << it[9].as<float>() << " ";
     cout << it[10].as<float>() << endl;
     
   }

}
   
   


void query2(connection *C, string team_color)
{
  string sql = "SELECT T.NAME FROM TEAM AS T, COLOR AS C WHERE T.COLOR_ID = C.COLOR_ID AND C.NAME = '" + team_color + "'; ";
  nontransaction N(*C);
  result output = N.exec(sql);

  cout << "NAME" << endl;
  result::iterator it;
  for (it = output.begin(); it != output.end(); it++)
    {
      cout << it[0].as<string>() << endl;
    }
}


void query3(connection *C, string team_name)
{

  string sql = "SELECT P.FIRST_NAME, P.LAST_NAME FROM PLAYER AS P, TEAM AS T WHERE P.TEAM_ID = T.TEAM_ID AND T.NAME = '" + team_name + "' " + "ORDER BY P.PPG DESC;";
  nontransaction N(*C);
  result output = N.exec(sql);

  cout << "FIRST_NAME LAST_NAME" << endl;
  result::iterator it;
  for (it = output.begin(); it != output.end(); it++)
    {
      cout << it[0].as<string>() << " ";
      cout << it[1].as<string>() << endl;
    }
}


void query4(connection *C, string team_state, string team_color)
{

  nontransaction N(*C);
  string sql = "SELECT P.FIRST_NAME, P.LAST_NAME, P.UNIFORM_NUM "  
                "FROM PLAYER AS P, TEAM AS T, STATE AS S, COLOR AS C "
                "WHERE P.TEAM_ID = T.TEAM_ID AND T.COLOR_ID = C.COLOR_ID AND T.STATE_ID = S.STATE_ID " 
                "AND S.NAME = '" + team_state + "' AND C.NAME = '" + team_color + "' ;"; 
  result output = N.exec(sql);
  cout << "FIRST_NAME LAST_NAME UNIFORM_NUM" << endl;
  result::iterator it;

  for (it = output.begin(); it != output.end(); it++)
    {
      cout << it[0].as<string>() << " ";
      cout << it[1].as<string>() << " ";
      cout << it[2].as<int>() << endl;
    }


}


/*void query5(connection *C, int num_wins)
{


  string sql =  "SELECT P.FIRST_NAME, P.LAST_NAME, T.NAME, T.WINS FROM PLAYER AS P, TEAM AS T WHERE P.TEAM_ID = T.TEAM_ID AND WINS " + " > " + num_wins + " ;";
  nontransaction N(*C);
  result output = N.exec(sql);
  
  cout << "FIRST_NAME LAST_NAME NAME WINS" << endl;
  result::iterator it;
  for (it = output.begin(); it != output.end(); it++)
    {
      cout << it[0].as<string>() << " ";
      cout << it[1].as<string>() << " ";
      cout << it[2].as<int>() << endl;
    }




}*/

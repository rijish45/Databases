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
}


void add_color(connection *C, string name)
{
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
}


void query2(connection *C, string team_color)
{
}


void query3(connection *C, string team_name)
{
}


void query4(connection *C, string team_state, string team_color)
{
}


void query5(connection *C, int num_wins)
{
}

#include "Monster.h"

//Monster Constructor
//Creates 3 tiers of Monster

Monster::Monster(int choice) : Character(0,0,0,0,0,0,0,0,0){
	switch (choice) {
	case 1:
		name = "Lock, Shock and Barrel";
		sig_move = "Triple Threat";
    monsterASCII = R"(                  /                                                                                 
                   ,/*                                                                              
                    *//.                                                                            
                     //*,                                                                           
                   ,//#(*                                                                           
           .**((((//.##(/                                                                           
          *##*(/(,((,(#((                     %%##(###%                                             
           %%((((, .**((%*,***,,             (.   %#&#*#%                      .          ,.        
            ##*& ,&(,/#%.%%#%##/               * #  .%(/                         #%&   ,%,   .      
             ,&       .  .%%##                   ..  &,                    ..   ,%%..  # #*   .     
            *#*.      ..&#&/                                                   /,.....    *.  ..    
          *(, ( *,   ..  */  (                  ,,      .                      .,#(.*,.//@,         
       *** /  * %#*#(. (/ ,(  #                  .&@% .                         ....*,,             
            # *(,//(%#, //*/@@@@@&              #...##                      (**/&&&&.. /%%          
         ,/#/#/(///((((#%%#((,(/(         (%%%%%##%#%%#&###,    .       .&.&@@&@&..%.%&(@@%#        
    &@@@@#/#/  (/////(#(*            ....%%%%&#%#%%###&&((#, (&      ..   (% #%%..%% %%%&&#&&.      
             .*,**/((#(((#%          ..       %#%%%%#%%%%    &&&     ..     &%&.%&&( #%%%@ /&.      
            ,(/*/////####((/#*               *#%%%%%#####    %              #%&&&&&.%# &&%          
            */((/(((/(/(@(&                   #%%#%%%%%%%  .                 &%%.%@@@@&.%%          
              @@@@/  %@@@/@@                  #%%%%&%%%%#/                   %((#%& @&%%%&          
           .@@ @@@    @@@@@@@              @@@&&%%%*&%#%%#@@                  .   .. ..  .          
           @@@@@@@    &@@@@@                @@@@@@@  @@@@@@@                  ..                    
             *&&                              @@@@   @@@@@@                                         
                                                                                                    
                                                                                                 )";
		stats["HP"] = 100;
		stats["ATK"] = 30;
		stats["DEF"] = 10;
    stats["MDEF"] = 5;
		stats["SPD"] = 5;
		stats["LVL"] = 5;
		stats["EXP"] = 200;
		stats["MONEY"] = 100;
    mItem = make_shared<Weapon>("Pumpkin Beam", 200, 20);
		break;
	case 2:
		name = "OOGIE BOOGIE";
		sig_move = "MASSACRE";
    monsterASCII = R"(               ...     ...                                                      
           ..*/,,,,..,,....,..                                 . ,  .           
         ..,(*../#.,....,,..*%..                                    ..,         
         ,(      ,*////**.,/@&....                            . , (.*,*         
                 ///,..,.,/&.,,,,.*,,,,.....                 .****,***.         
                 .*,*##***/*,,,,/&&.,,.........,,...        ,,,,,****           
                  ,*//**,..(%@@@@&..**,,,..,,,......,.,..   ,****,**,           
                .*(&&@@&&&&&&&&&&.,*//**,,,..,...,,....../,,*****//*,           
             ../.,/**%&&&&&&&&%,.,//****,,**,,,,,,*,,,****,*******#**           
           .,/,,,**/((/**,..,,,,///**,,..,**/////**,,***,,,,*,,,***(,,          
          .#..,***,**/((/(((/////***,,,,,,,***//////**(******////**/,           
        .*./,..,,,,*,,**//////****,,,,,,,,,,,**/(((////*///***/***//*           
       .(,,***/////**,,,,,,,*,***,,,,,,,,,,,,,,*//(##/////((/******/            
       ,,,,**/((##,*****,,.,,,,,,,,............,,*/(####///(((//***             
      (,*,,,*/(##*,******,,,....,,,,......,,,,,..,,*//(((.   ..                 
    ..,,*///((((#*****////****,,,**,,,,,,,,,,,,,.,..,*/(%*                      
    ,,,,,**/(((#(******////////***//**,,,,,...,,,,,,..*,*(,                     
    ,,,***/(((. ,********////////////***,,,,,,*******,,,,,/,                    
    ,*/(((((,   ***/**,,*******/////////////////*/***,.,,,.#*,                  
    ,,*((((     *////**,,,,,,,,,,,,**//////***,,,,,,,,,,,,../,..                
     ,*/((     ,**/////**,,,,,,***,,,,,,,,.,,,,,,,,,.....,,../,..               
      */(/    *****////(////****,,*,,..,,,,,**,,,........,*,,./,,               
       **.   ****////*/////***,*,,,,,,****,,,,,,,*****,,.,,,,*%/.               
            ,****//////*******,,,*******,,,,,,,**///////******,*,.              
           .**///////(//////***,,,*****,,,,***********///*****,*,...            
           ,**/(///((/////////*******,********/******,,,,,,,,,,.,#..            
          ,,***/(#(((((////////////////////////////////****,,,,,,*,,.           
          .*****/((####(((/((((((///////////////////////******,,,/**,.          
          .**//////((((####(((((((((((((((((((((##(((/////////***,./*.          
           .*/((((((((##((((#((#######(((######((((///((///////**,,.**          
           .//(((###(((#####%%%%%%%%%%%##########(((/(//********,,,..*.         
        .,,*/(((((#%%%%*  .*(###############((((((((///////****,,,,,,.*         
         /((((/(*,.                           ./###((((((((((((((/*,,,.*,       
                                                        .((((((((((/**,/*       
                                                            ,(((//**,,.....,.   
                                                                   .**/((/,.   )";
		stats["HP"] = 420;
		stats["ATK"] = 75;
		stats["DEF"] = 65;
    stats["MDEF"] = 85;
		stats["SPD"] = 50;
		stats["LVL"] = 15;
		stats["EXP"] = 2000;
		stats["MONEY"] = 2500;
    mItem = make_shared<Potion>("Hyper Potion", 500, 80);
    break;
  case 3:
  //return a weak monster here
		name = "Rats";
		sig_move = "BITE";
    monsterASCII = R"(  __QQ
 (_)_">
_) )";
		stats["HP"] = 50;
		stats["ATK"] = 10;
		stats["DEF"] = 10;
    stats["MDEF"] = 5;
		stats["SPD"] = 5;
		stats["LVL"] = 1;
		stats["EXP"] = 100;
		stats["MONEY"] = 100;
    mItem = make_shared<Potion>("Potion", 30, 10);
		break;
  case 4:
    //return a weak monster here
		name = "Bats";
		sig_move = "Wing swat";
    monsterASCII = R"(        _   ,_,   _
       / `'=) (='` \
      /.-.-.\ /.-.-.\ 
   `      "      `)";
		stats["HP"] = 50;
		stats["ATK"] = 5;
		stats["DEF"] = 10;
    stats["MDEF"] = 8;
		stats["SPD"] = 5;
		stats["LVL"] = 1;
		stats["EXP"] = 100;
		stats["MONEY"] = 100;
    mItem = make_shared<Potion>("Potion", 30, 10);
		break;
  case 5:
    //return a weak monster here
		name = "Wild cats";
		sig_move = "Paw swing";
    monsterASCII = R"(    |\__/,|   (`\
  _.|o o  |_   ) )
-(((---(((--------)";
		stats["HP"] = 50;
		stats["ATK"] = 14;
		stats["DEF"] = 10;
    stats["MDEF"] = 15;
		stats["SPD"] = 5;
		stats["LVL"] = 1;
		stats["EXP"] = 100;
		stats["MONEY"] = 100;
    mItem = make_shared<Potion>("Potion", 30, 10);
		break;
  case 6:
    name = "Goblins";
		sig_move = "Swipe";
    monsterASCII = R"(              ,      ,
            /(.-""-.)\
        |\  \/      \/  /|
        | \ / =.  .= \ / |
        \( \   o\/o   / )/
         \_, '-/  \-' ,_/
           /   \__/   \
           \ \__/\__/ /
         ___\ \|--|/ /___
       /`    \      /    `\
   /       '----'       \)";
		stats["HP"] = 100;
		stats["ATK"] = 20;
		stats["DEF"] = 15;
    stats["MDEF"] = 10;
		stats["SPD"] = 3;
		stats["LVL"] = 5;
		stats["EXP"] = 200;
		stats["MONEY"] = 200;
    mItem = make_shared<Potion>("Hyper Potion", 30, 10);
		break;
  case 7:
  name = "Ghoul";
		sig_move = "Spook";
    monsterASCII = R"(            .--,
           /  (
          /    \
         /      \ 
        /  0  0  \
((()   |    ()    |   ()))
\  ()  (  .____.  )  ()  /
 |` \_/ \  `""`  / \_/ `|
 |       `.'--'.`       |
  \        `""`        /
   \                  /
    `.              .'    ,
     |`             |  _.'|
     |              `-'  /
     \                 .'
      `.____________.-')";
		stats["HP"] = 100;
		stats["ATK"] = 10;
		stats["DEF"] = 50;
    stats["MDEF"] = 10;
		stats["SPD"] = 15;
		stats["LVL"] = 5;
		stats["EXP"] = 200;
		stats["MONEY"] = 200;
    mItem = make_shared<Potion>("Hyper Potion", 30, 10);
		break;
  case 8:
  name = "The Mayor";
		sig_move = "Throws Hat";
    monsterASCII = R"(                /&@@&&&.                                                        
                &@@@@@&&&                                                       
                 &@@@@@@&&                                                      
                   &@@@@@@&                                                     
                     &@@@@@&%                                                   
                      %@@@@@&&                                                  
                        &@@@@@&                                                 
                         /&@@&@&                                                
                           &@@@&&                                               
                            &@@@@%                                              
                              &@@&%                                             
                               &@&&%                                            
                                &&@&&                                           
                                 &&&&*                                          
                                  &@@&&                                         
                                   &&@&%                                        
                                    &&&&&                                       
                                     &&##/                                      
                                     (###(/                                     
                                     (###(#/#/                                  
                                 (&&&&&&&&&@@&&&&&                              
                                &&&@@&@@@@@@@&&&&@                              
                                   @&@@@&@&&(/                                  
                                   *,((* &,/@,*                                 
                                  .,#@./%,,(,,,                                 
                                 ,#,,,*,&,,,,*,,                                
                                ,,,. #/**/#* #,,,                               
                             %&*,,,&##@%@&%@&.,..,                              
                          ,&&&,,,,,,,//   /,,,,,...@@&&                         
                          &&&& .,,...,,,,,,,,,,,,   &@&&%                       
                         &&&&&&&,..    .  /,,,**..,&@&&&&&                      
                   *//(#(#&&&&&&&&#.,. #%&, .,..*&@@@@&&&%/***                  
             *((((####%##(#%%%%%#%@@@&@#@%@@&*.@@@@@@&&@&#%%#((((*,             
         /(####%%%%%%%%%#(%%%%%%%##%#&@@&  @@@@@@@&&&%##%%%%%%%#(####((,        
      /(/%%%%%%%%%%%%%&%#%%%%%%%%%#%%#%%%%(%%%%%##%%(#(#%%(&%%%%%%%%%%%%/**/    
   ,....,(#%%%%%%%%%% %%&%%%%%%%%%%%%%&%@%#%%###%%####%#%%%(%%%%%####%#(#,.,,   
 ,%.,.,,.,,#&%%%%%#  #%%%%%%%%%%%%%%&%(%%%#%%####*(#*##%##%#    %%%%%%#**,/../* 
 ,..,     (%%%%      %%%%%%%%%%%%%%%%%#%#%%@%#/(##%#((%(%%##         ##%    **,*
                    #%%%%%%%%%%%%%%%%%%#&%%%%&(#.*@/@/((%#(#(                   
                    #%%%%%%%%%&%%%%%%%#&%%%/((#(, @. ((/##&((                   
                    ##%%%%%%%%%%%%%%%#%%%%%#&(((///(((&#((#//                   
                    #%%%%%%%%#%%%%%#%%%&%&%%@%#&(((/%#(#/(#/                    
                       (#%%%%%%%%%%#%%%%%#(%@&##@##%(#####                      
                          &@@#####%#%%%%%%##%(##&#%(@@@&##                      
                           .&&&@@@@@@@@/  &(#((@@@@@&&                          
                              &%@&&&@@*    @@@@&&&&%                            
                                 &&&@@&   (&&&&&&                               
                                  %&&&&&  &&&&@&                                
                                   &&&       &&&     )";
		stats["HP"] = 100;
		stats["ATK"] = 25;
		stats["DEF"] = 25;
    stats["MDEF"] = 25;
		stats["SPD"] = 5;
		stats["LVL"] = 5;
		stats["EXP"] = 200;
		stats["MONEY"] = 200;
    mItem = make_shared<Potion>("Hyper Potion", 30, 10);
		break;
    case 9:
      name = "Mimic";
		sig_move = "Chomp";
    monsterASCII = R"(                            #@@@%/*.    ********(@@@                         
                 @&(/@//(//(/*/(/*/    ,/********(&&/#//@ .                  
               @ @((%((%(/#(/&////%@@/*@//////((////#(((%@ @                 
              *(.@##@#(#(#((((&@@       @@@@@@&#((#(##%##@ #                 
              ##@%%%%%@     #@@@@@@@@&@@&&&&@@@@@@@   #@@@                   
              , (   .@#(@@.  .  # .@ @  *   .@     , &(%#%%                  
              (/@%. @  @ @, @@  @ .@@@ @@ @ &@@ %@ , % * ./@                 
                @@@%%@@@@@@@@@@@@@@@@@@@@@@@@@@ @@@@@.@@. &                  
                  *&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  #                  
                   @,@ @ @ @@  @@ &@ @@@@@@@@@@@/( @,( &   #                 
                 &#@. .(*  *(         @(/,. &@@##(@@.@.*@&#                  
                % @@%%%%%%%%(&@&%%@(&&#@@###,,@####,@%%%&@&                  
                ,  ######@  @@@@&      .@&###,&###//@%##  &                  
                   @######   &%#&    %  @@%##*@###/%@%%@                     
                 @ ,&#&%##(  &###@  %@@ #@%##*@###/.@((  @   &(              
                  & @%%#%#@, @####& .&@@&@@%##*%###, &( @  &@@               
                   @.@@%###.  #######((##@@@&%#(*#&#####,*(@                 
                 ###%%%%&@@@@@@@@@%##########@@%%%#####@@**                  )";
		stats["HP"] = 420;
		stats["ATK"] = 50;
		stats["DEF"] = 50;
    stats["MDEF"] = 50;
		stats["SPD"] = 30;
		stats["LVL"] = 9;
		stats["EXP"] = 300;
		stats["MONEY"] = 500;
    mItem = NULL;
		break;
    
	}
	
}

//Display Monster Stats
ostream& operator<<(ostream& os, Monster* pm) {
	os << "Monster Stats..." << endl;
	os << "Monster: " << pm->getName() << endl;
	os << "LEVEL " << pm->getStat("LVL") << endl;
	os << "HEALTH: " << pm->getStat("HP") << endl;
	os << "ATTACK: " << pm->getStat("ATK") << endl;
	os << "DEFENSE: " << pm->getStat("DEF") << endl;
	os << "SPEED: " << pm->getStat("SPD") << endl;
	return os;
}

//Monster Signature Move
void Monster::signature(Character* c) {
	cout << "SIGNATURE MOVE: " << sig_move << endl;
	c->setHP(-2 * stats["ATK"]);
	cout << "Damage: " << 2 * stats["ATK"] << endl;
}

//Get Item from Monster
shared_ptr<Item> Monster::getItem() {
	return mItem;
}

void Monster::attack(shared_ptr<Character> c) {
  cout<< name<< " uses " << this->sig_move <<"!"<<endl;
  int damage = 0;
  if (stats["ATK"] - (c->getStat("DEF") > 0) / 5) damage = stats["ATK"] - (c->getStat("TEMPDEF")/5);
  if(damage < 0){
    damage = 1;
  }
	c->setHP(-damage);
	cout << "Damage: " << damage << endl;
}

void Monster::defend(shared_ptr<Character> c) {
	cout << name<<  " DEFENDS!" << endl;
	stats["HP"] += (stats["DEF"] - c->getStat("ATK"));
	cout<<"They are protected against your attack!"<<endl;
}

void Monster::printMonsterStats(){
  cout << "LEVEL " << this->getStat("LVL") << endl;
	cout << "HEALTH: " << this->getStat("HP") << endl;
  cout << "ATTACK: " << this->getStat("ATK") << endl;
	cout << "DEFENSE: " << this->getStat("DEF") << endl;
	cout << "SPEED: " << this->getStat("SPD") << endl;
	cout << "EXP: " << this->getStat("EXP") <<endl;
  cout << "PUMPKIN SEEDS: " << this->getStat("MONEY") << endl<<endl;

}

string Monster::getMonsterASCII(){
  return monsterASCII;
}
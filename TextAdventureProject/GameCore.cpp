#include "GameCore.h"
#include "CommandParser.h"
#include <stdio.h>
#include <string>
#include <Windows.h>

RoomData createRoom(const std::string& inName, const std::string& inDescription, bool hasKey, bool canCallHere, bool hasPhone)
{
	RoomData room = {};
	room.Name =inName;
	room.Description = inDescription;
	room.HasKey = hasKey;
	room.CanCallHere = canCallHere;
	room.HasPhone = hasPhone;
	

	return room;
}


void AddExitToRoom(RoomData& roomToEdit, const std::string& exitName, int targetRoomIndex, bool isLocked)
{
	RoomExitdata exit = {};
	exit.Name = exitName;
	exit.TargetRoomIndex = targetRoomIndex;
	exit.Locked = isLocked;
	roomToEdit.Exits.push_back(exit);


}


void InitializeGame(PlayerState& playerState, WorldState& worldState)
{
	
	printf("*BEEP*BEEP*BEEP*BEEP*\n");
	Sleep(2000);
	printf("You wake up to you alarm clock blaring.\n");
	printf("The alarm clocks reads: 9:23 AM.\n");
	Sleep(2000);
	printf("You slam the off button on your alarm clock.\n");
	printf("You slowly get up from your bed, vision blurry, head still spining from the night before.\n");
	printf("\n");
	Sleep(5000);
	printf("Your vision finally straightens out and you see a piece of paper with writing on it.\n");
	Sleep(2000);
	printf("The paper reads:'Rough night huh... you tried ordering a pizza like 5 times last night and were writing all over the walls.\n");
	printf("Something about how good the crust is or whatever... I've gone out to get some Gatorade and other hangover cures.\n");
	printf("Order a pizza and some breadsticks, I'll be back in 25 minutes.'\n");
	printf("- your roommate Zack \n");
	printf("p.s. you threw you phone around in the living room and your bathroom is locked.\n");
	Sleep(5000);
	printf("\n\n");
	

	playerState.CurrentRoomIndex = 0;
	playerState.WantstoLook = true;
	playerState.HasKey = false;
	playerState.WantsToCall = false;
	playerState.HasPhone = false;
	

	// Player's Bedroom
	RoomData bedroom = createRoom("Bedroom", "Familiar and Messy.", false, false, false);
	AddExitToRoom(bedroom, "bathroom", 1, true);
	AddExitToRoom(bedroom, "hallway", 2, false);
	worldState.Rooms.push_back(bedroom);
	
	
	// Player's Bathroom
	RoomData bathroom = createRoom("Bathroom", " 703-35... written in red lipstick on the mirror.", false, true, false);
	AddExitToRoom(bathroom, "bedroom", 0, false);
	//AddExitToRoom(bathroom, "room3", 2, false);
	worldState.Rooms.push_back(bathroom);


	// Hallway
	RoomData hallway = createRoom("Hallway", "2- written in sharpie on the wall.", false, false, false);
	AddExitToRoom(hallway, "bedroom", 0, false);
	AddExitToRoom(hallway, "kitchen", 3, false);
	AddExitToRoom(hallway, "zacksroom", 5, false);
	worldState.Rooms.push_back(hallway);


	// Kitchen
	RoomData kitchen = createRoom("Kitchen", "Wet floor. Garbage can overflowing. Refridgerator buzzing. 0990 scribbled on floor.", false, false, false);
	AddExitToRoom(kitchen, "hallway", 2, false);
	AddExitToRoom(kitchen, "livingroom", 4, false);
	worldState.Rooms.push_back(kitchen);


	// Living Room
	RoomData livingroom = createRoom("Living Room", "More trash strewn about. A Phone sticks out of couch cushions.", false, false, true);
	AddExitToRoom(livingroom, "kitchen", 3, false);
	//AddExitToRoom()
	worldState.Rooms.push_back(livingroom);


	// Zack's Bedroom
	RoomData zacksroom = createRoom("Zack's Bedroom", "Unfamiliar and cleaner than yours. ", false, false, false);
	AddExitToRoom(zacksroom, "zacksbathroom", 6, false);
	AddExitToRoom(zacksroom, "hallway", 2, false);
	worldState.Rooms.push_back(zacksroom);


	// Zack's Bathroom 
	RoomData zacksbathroom = createRoom("Zack's Bathroom", "Clean and refreshing smell with a key on the counter of the sink.", true, false, false);
	AddExitToRoom(zacksbathroom, "zacksroom", 5, false);
	worldState.Rooms.push_back(zacksbathroom);



}

void GetInput(PlayerState& playerState, const WorldState& worldState)
{
	
	playerState.WantstoLook = false;
	playerState.DesiredExit = "";
	playerState.DesiredPickup = "";
	playerState.DesiredGrab = "";


	printf("What do you do?\n");
	printf("> ");
	TextAdventureCommand command = ParseAdventureCommand();
	if (command.Verb == "quit")
	{
		playerState.WantsToExit = true;
	}

	else if (command.Verb == "look") 
	{
		playerState.WantstoLook = true;
	}

	else if (command.Verb == "go")
	{
		playerState.DesiredExit = command.Parameter;
	}

	else if(command.Verb == "get")
	{
		playerState.DesiredPickup = command.Parameter;
	}

	else if (command.Verb == "grab")
	{
		playerState.DesiredGrab = command.Parameter;
	}

	else if (command.Verb == "call")
	{
		playerState.WantsToCall = true;
	}

	else if (command.Verb == "help")
	{
		printf("Command List: look, quit, go [place], get keys, call, grab [thing]\n");
	}
	else
	{
		printf("I don't understand\n");
	}
	printf("\n");

}

void RenderGame(const PlayerState& playerState, const WorldState& worldState)
{

	if (playerState.WantstoLook) 
	{
		RoomData currRoom = worldState.Rooms[playerState.CurrentRoomIndex];
		printf("===================================\n");
		printf("LOCATION: %s \n", currRoom.Name.c_str());
		printf("Description: %s \n\n", currRoom.Description.c_str());
		
		if (currRoom.HasKey)
		{
			printf("There is a key in this room!\n\n");
		}

		if (currRoom.HasPhone)
		{
			printf("Your phone is in this room!\n\n");
		}

		printf("EXITS:\n");
		for (unsigned int i = 0; i < currRoom.Exits.size(); i++)
		{
			printf("%s\n", currRoom.Exits[i].Name.c_str());
		}
		printf("\n");
		if (playerState.HasKey && playerState.HasPhone)
		{
			printf("INVENTORY:\n");
			printf("Key\n");
			printf("Phone\n");
		}
		else if (playerState.HasKey) {
			printf("INVENTORY:\n");
			printf("Key\n");
		}
		else if (playerState.HasPhone) {
			printf("INVENTORY:\n");
			printf("Phone\n");
		}

		
		printf("\n");
	}



}

void UpdateGame(PlayerState& playerState, WorldState& worldState)
{
	RoomData& currRoom = worldState.Rooms[playerState.CurrentRoomIndex];

	if (playerState.DesiredExit != "") 
	{
		bool foundExit = false;

		for (unsigned int i = 0; i < currRoom.Exits.size(); i++)
		{
			if (playerState.DesiredExit == currRoom.Exits[i].Name)
			{
				foundExit = true;


				if (!currRoom.Exits[i].Locked)
				{
					playerState.CurrentRoomIndex = currRoom.Exits[i].TargetRoomIndex;
					playerState.WantstoLook = true;
				}
				else
				{
					if (playerState.HasKey)
					{
						playerState.CurrentRoomIndex = currRoom.Exits[i].TargetRoomIndex;
						playerState.WantstoLook = true;
					}
					else 
					{
						printf("The door doesn't budge! Gotta find a key around here somewhere.\n");
					}
					
				}
			}

		}
		if (!foundExit)
		{
			printf("I could not find an exit called '%s'\n\n", playerState.DesiredExit.c_str());
		}

	}
	else if (playerState.DesiredPickup != "")
	{
		if (playerState.DesiredPickup == "key")
		{
			if (currRoom.HasKey)
			{
				printf("Oooh, a key!\n");
				playerState.HasKey = true;
				currRoom.HasKey = false;

			}
			else
			{
				printf("Hmm.. theres no key here\n");
			}
		}
		else
		{
			printf("I dont know what a '%s' is ...\n", playerState.DesiredPickup.c_str());
		}
	}
	else if (playerState.DesiredGrab != "")
	{
		if (playerState.DesiredGrab == "phone")
		{
			if (currRoom.HasPhone)
			{
				printf("Your cracked and low battery iPhone.\n");
				playerState.HasPhone = true;
				currRoom.HasPhone = false;
			}
		}
		else
		{
			printf("There's nothing to grab!");
		}
	}
	else if (playerState.WantsToCall)
	{
		if (currRoom.CanCallHere)
		{
			printf("Congratualtions! A Hungover you was able to find your phone and order a pizza!\n");
			printf("You're a winner in your eyes.\n");
			printf("As you jump around you get lightheaded and stumble back and fall into you bed and passout.\n");
			playerState.WantsToExit = true;
		}
		else
		{
			printf("You can't call here! You need to find the rest of the Phone #!\n");
		}
	}
}

void CleanupGame(PlayerState& playerState, WorldState& worldState)
{
	printf("Quitting...\n\n");
}
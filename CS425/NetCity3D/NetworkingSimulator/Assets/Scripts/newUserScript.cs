using UnityEngine;
using System.Collections;

public class newUserScript : MonoBehaviour {
	public string name = "";
	public string pass = "";

	GameObject playerMemory;
	gameManager playerScript;

	bool sameUserName;

	// This is if the user is the professor and they want to change the values for soemthings
	bool professor;

	// These are the values for the car color that might be bad based on the professor preference
	public bool red;
	public bool blue;
	public bool green;
	public bool yellow;

	// These are the values for the car size that might be bad based on the professor preference	\
	public bool large;
	public bool median;
	public bool small;

	// Bool if the bad car upgrades have been chosen
	public bool badCarsChosen;

	// These variables are used for toggling what the professor wants in terms of the type of car it is
	public bool ambulance;
	public bool fireTruck;
	public bool Tanker;
	public bool Truck;
	public bool Hearse;
	public bool IceCream;
	public bool policeCar;
	public bool Taxi;

	// Use this for initialization
	void Start () {
		//assigns playerManager which is not destroyed throughout scenes
		playerMemory = GameObject.Find ("GameObject");
		playerScript = playerMemory.GetComponent<gameManager> ();	
		professor = false;
	}
	
	// Update is called once per frame
	void Update () {
	
	}

	//sets up UI and also inputs
	void OnGUI()
	{
		if (!professor) {
			float width = 300.0f;
			float height = 35.0f;
			float t = 20.0f;

			GUI.skin = Resources.Load ("Buttons/ButtonSkin") as GUISkin;
			//to check if the user has actually inputted things in user and password
			bool unInput = false;
			bool pInput = false;

			//create the labels and textfields for username and password

			GUI.Label (new Rect ((Screen.width / 2) - width / 2, (Screen.height / 4) - 50, width, height), "Create Username");


			name = GUI.TextField (new Rect ((Screen.width / 2) - width / 2, (Screen.height / 4) + height + 5 - 50, width, height), name.Trim (), 30);

			GUI.Label (new Rect ((Screen.width / 2) - width / 2, (Screen.height / 4) + (2 * height) + 5 - 50, width, height), "Create a Password");

			pass =  GUI.PasswordField(new Rect ((Screen.width / 2) - width / 2, (Screen.height / 4) + (3 * height) + 5 - 50, width, height), pass, "*"[0], 30);

			//check if the user has inputted the username
			//if they have don't display line prompting for username
			if (name != "" && name != "professor") {
				unInput = true;
			}
			//else show text that prompts for the username
			else {
				unInput = false;
				GUI.Label (new Rect ((Screen.width / 2) - width / 2, (Screen.height / 4) + (4 * height) + 5 - 50, width + 200, height), "That username cannot be selected, please enter a valid name");
			}

			//check if the user has inputted the password
			//if they have don't display text prompting for password
			if (pass != "") {
				if (name == "professor" && pass == "professor") {
					unInput = true;
				}
				pInput = true;
			} 
			//else do display the text
			else {	
				pInput = false;
				GUI.Label (new Rect ((Screen.width / 2) - width / 2, (Screen.height / 4) + (5 * height) + 5 - 50, width + 200, height), "That password cannot be selected, please enter a valid password");

			}

			GUI.color = Color.white;

			// This button is for create Profile
			if (GUI.Button (new Rect (Screen.width / 2, (Screen.height / 2) + 105, GUI.skin.button.fixedWidth, GUI.skin.button.fixedHeight), "Create Profile")) {
				//check if username is taken or not
				if (playerScript.checkForUser (name)) { 		
					GUI.Label (new Rect (Screen.width / 2, (Screen.height / 2) + 195, 190, 60), "Username is already taken");

				} else {
					//if user has inputted the password and username then go to next scene
					if (unInput == true && pInput == true) {	
						if (name == "professor" && pass == "professor" && professor == false) {
							professor = true;
						} else {
							playerScript.setUserName (name);
							playerScript.setPassword (pass);
					


							Application.LoadLevel ("GameTutorials");
						}
					}
					//else don't do anything until they do
				}
			}

			// This button is for going back to the mainMenu
			if (GUI.Button (new Rect ((Screen.width) / 10, (Screen.height) / 10, GUI.skin.button.fixedWidth, GUI.skin.button.fixedHeight), "Main Menu")) {
				Application.LoadLevel ("StartMenu");
				
			}
		} 
	else {
			int upgradeOneGUIRow =  75;
			int upgradeTwoGUIRow = 345;
			int upgradeThreeGUIRow  = 615;

			int upgradeOneGUICol = 50;
			int upgradeTwoGUICol = 250;
			int upgradeThreeGUICol = 450;

			GUI.skin = Resources.Load ("Buttons/ShopSkin") as GUISkin;
			GUIStyle guiStyle = GUI.skin.GetStyle ("Shop");


			int offset = 20;
			float Twidth = GUI.skin.toggle.fixedWidth;
			float Theight = 30f;


			// Otherwise, place an interactable GUI button onto the screen called OpenShop
			GUI.BeginGroup(new Rect((Screen.width/2)-400, Screen.height/2 -300, 800, 750));


			GUI.Box (new Rect (0, 0, 0, 0), "Bad Car Options");

			ambulance = GUI.Toggle(new Rect(Twidth * 2 + offset, 140, Twidth, Theight), ambulance, "Ambulance");
			fireTruck = GUI.Toggle(new Rect(Twidth * 2 + offset, 215, Twidth, Theight), fireTruck, "Fire Truck");
			Tanker = GUI.Toggle(new Rect(Twidth * 2 + offset, 290, Twidth, Theight), Tanker, "Oil Truck");
			Truck = GUI.Toggle(new Rect(Twidth * 2 + offset, 365, Twidth, Theight), Truck, "Truck");
			Hearse = GUI.Toggle(new Rect(Twidth * 2 + offset, 440, Twidth, Theight), Hearse, "Hearse");
			IceCream = GUI.Toggle(new Rect(Twidth * 2 + offset, 515, Twidth, Theight), IceCream, "Ice Cream");
			policeCar = GUI.Toggle(new Rect(Twidth * 2 + offset, 590, Twidth, Theight), policeCar, "Police Car");

			small = GUI.Toggle(new Rect(Twidth + offset, 140, Twidth, Theight), small, "Small");
			median = GUI.Toggle(new Rect(Twidth + offset, 215, Twidth, Theight), median, "Medium");
			large = GUI.Toggle(new Rect(Twidth + offset, 290, Twidth, Theight), large, "Large");

			red = GUI.Toggle (new Rect (offset, 80, Twidth, Theight), red, "Red");
			green = GUI.Toggle (new Rect (offset, 155, Twidth, Theight), green, "Green");
			blue = GUI.Toggle (new Rect (offset, 230, Twidth, Theight), blue, "Blue");
			yellow = GUI.Toggle (new Rect (offset, 305, Twidth, Theight), yellow, "Yellow");


			if (GUI.Button(new Rect(offset, 550, GUI.skin.button.fixedWidth, 50), "Change")){
				// Send the information to the game manager
				playerScript.setGameMangerBools (red, green, blue, yellow, small, median, large, ambulance, fireTruck, Tanker, Truck, Hearse, IceCream, policeCar);

				// Clear the booleans
				clear();

				// Set professor to false so the normal gui layout appears
				professor = false;

				playerScript.badCarsChosen = true;
			}

			if (GUI.Button(new Rect(offset, 650, GUI.skin.button.fixedWidth, 50), "Cancel Change")){
				clear();
				professor = false;
			}
			GUI.EndGroup ();	

		}
	}

	// This function is used to clear all of the boolean variables to false
	void clear(){
		red = green = blue = yellow = small = median = large = ambulance = fireTruck = Tanker = Truck = Hearse = IceCream = policeCar = false;
	}

}

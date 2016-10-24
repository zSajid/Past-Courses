using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class shopMenu : MonoBehaviour {
	private bool shopOpen; // This is to check if the shop has been opened and ready to show it to the user
	private gameManager player; // This is to check for player manipulation, cash, levels etc.

	private int security_one_cost; // This is the amount the player has to pay for security level 1 upgrade
	private int security_two_cost; // This is the amount the player has to pay for security level 2 upgrade
	private int security_three_cost; // This is the amount the player has to pay for security level 2 upgrade

	private int honey_one_cost; // This is the amount the player has to pay for security level 1 upgrade
	private int honey_two_cost; // This is the amount the player has to pay for security level 2 upgrade
	private int honey_three_cost; // This is the amount the player has to pay for security level 2 upgrade


	// This will be for the size of the GUI buttons
	private int guiWidth;
	private int guiHeight;

	// This is the images for each of the different security types
	Texture2D securityOneImage;
	Texture2D securityTwoImage;
	Texture2D securityThreeImage;

	// This is the content for which the images will be held to
	GUIContent securityOneImageContainer;
	GUIContent securityTwoImageContainer;
	GUIContent securityThreeImageContainer;

	// String value which will detect what type of security it is. The range can be L1, L2, L3
	private string securityType;

	// These are the values for car color that it will detect what car colors are allowed
	public bool red;
	public bool blue;
	public bool green;
    public bool yellow;

	// These are the values for the size of the car which the gate will detect
	public bool large;
	public bool median;
	public bool small;

	// Bool if upgrade chosen
	public bool upgradeChosen;

	// This is the toggle boolean variables for the different types of car user can choose from
	public bool ambulance;
	public bool fireTruck;
	public bool Tanker;
	public bool Truck;
	public bool Hearse;
	public bool IceCream;
	public bool policeCar;
	public bool Taxi;

	public int cost = 0;

    public List<string> honeyFlags = new List<string>();
    public int honeyLevel = 1;

	public List<string> securityFlags = new List<string>();
	public int firewallLevel = 1;


	// Use this for initialization
	void Start () {
		player = GameObject.Find ("GameObject").GetComponent<gameManager> ();
		// This is going to initialize all of the variables at the get go
		shopOpen = false; // The shop will be closed from the very beginning unless otherwise noted
		security_one_cost = 0; // This is the amount the player has to pay for security level 1 upgrade
		security_two_cost = (int)(player.cash * 0.40); // This is the amount the player has to pay for security level 2 upgrade
		security_three_cost = (int)(player.cash * 0.80); // This is the amount the player has to pay for security level 2 upgrade


		honey_one_cost = (int)(player.cash * 0.30);
		honey_two_cost = (int)(player.cash * 0.55);
		honey_three_cost = (int)(player.cash * 0.85);

		// Initialize the images
		securityOneImage = 	(Texture2D) Resources.Load ("Images/FirewallIcon");
		securityTwoImage = (Texture2D)Resources.Load ("Images/HoneyPotIcon");
		securityThreeImage = (Texture2D)Resources.Load ("Images/Security");

		securityOneImageContainer = new GUIContent();
		securityOneImageContainer.image = securityOneImage;

		securityTwoImageContainer = new GUIContent();
		securityTwoImageContainer.image = securityTwoImage;

		securityThreeImageContainer = new GUIContent();
		securityThreeImageContainer.image = securityThreeImage;

		// String value is set to a default value
		securityType = " ";

		// Set default values as false
		red = false;;
		blue = false;
		green = false;
        yellow = false;
		large = false;
		median = false;
		small = false;
		upgradeChosen = false;
	}

	// Update is called once per frame
	void Update () {

	}

	void OnGUI(){

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


		if (shopOpen == true) {

			// Otherwise, place an interactable GUI button onto the screen called OpenShop
			GUI.BeginGroup(new Rect((Screen.width/2)-400, Screen.height/2 -300, 800, 750));

			if (upgradeChosen) {

				if (securityType == "FL1" || securityType == "FL2"  || securityType == "FL3"){
					GUI.Box(new Rect(0, 0, 0, 0), "Purchase Options");
					honeyLevel = 1;

					red    = GUI.Toggle(new Rect(offset, 80, Twidth, Theight), red, "Red");
					green  = GUI.Toggle(new Rect(offset, 155, Twidth, Theight), green, "Green");
					blue   = GUI.Toggle(new Rect(offset, 230, Twidth, Theight), blue, "Blue");
					yellow = GUI.Toggle(new Rect(offset, 305, Twidth, Theight), yellow, "Yellow");

					//This is to check for what type of color the security gate will look for
					if (red && !securityFlags.Contains("Red")) securityFlags.Add("Red");
					else if (!red && securityFlags.Contains("Red")) securityFlags.Remove("Red");

					else if (green && !securityFlags.Contains("Green")) securityFlags.Add("Green");
					else if (!green && securityFlags.Contains("Green")) securityFlags.Remove("Green");

					else if (blue && !securityFlags.Contains("Blue")) securityFlags.Add("Blue");
					else if (!blue && securityFlags.Contains("Blue")) securityFlags.Remove("Blue");

					else if (yellow && !securityFlags.Contains("Yellow")) securityFlags.Add("Yellow");
					else if (!yellow && securityFlags.Contains("Yellow")) securityFlags.Remove("Yellow");

					if (securityType == "FL2" || securityType == "FL3"){
						firewallLevel = 2;

						small  = GUI.Toggle(new Rect(Twidth + offset, 80, Twidth, Theight), small, "Small");
						median = GUI.Toggle(new Rect(Twidth + offset, 155, Twidth, Theight), median, "Medium");
						large  = GUI.Toggle(new Rect(Twidth + offset, 230, Twidth, Theight), large, "Large");

						//This is to check for what type of color the security gate will look for
						if (small && !securityFlags.Contains("Small")) securityFlags.Add("Small");
						else if (!small && securityFlags.Contains("Small")) securityFlags.Remove("Small");

						else if (median && !securityFlags.Contains("Medium")) securityFlags.Add("Medium");
						else if (!median && securityFlags.Contains("Medium")) securityFlags.Remove("Medium");

						else if (large && !securityFlags.Contains("Large")) securityFlags.Add("Large");
						else if (!large && securityFlags.Contains("Large")) securityFlags.Remove("Large");

					}

					if (securityType == "FL3"){
						firewallLevel = 3;

						ambulance = GUI.Toggle(new Rect(Twidth * 2 + offset, 80, Twidth, Theight), ambulance, "Ambulance");
						fireTruck = GUI.Toggle(new Rect(Twidth * 2 + offset, 155, Twidth, Theight), fireTruck, "Fire Truck");
						Tanker    = GUI.Toggle(new Rect(Twidth * 2 + offset, 230, Twidth, Theight), Tanker, "Oil Truck");
						Truck     = GUI.Toggle(new Rect(Twidth * 2 + offset, 305, Twidth, Theight), Truck, "Truck");
						Hearse    = GUI.Toggle(new Rect(Twidth * 2 + offset, 380, Twidth, Theight), Hearse, "Hearse");
						IceCream  = GUI.Toggle(new Rect(Twidth * 2 + offset, 455, Twidth, Theight), IceCream, "Ice Cream");
						policeCar = GUI.Toggle(new Rect(Twidth * 2 + offset, 530, Twidth, Theight), policeCar, "Police Car");

						//This is to check for what type of color the security gate will look for
						if (ambulance && !securityFlags.Contains("Ambulance")) securityFlags.Add("Ambulance");
						else if (!ambulance && securityFlags.Contains("Ambulance")) securityFlags.Remove("Ambulance");

						else if (fireTruck && !securityFlags.Contains("FireTruck")) securityFlags.Add("FireTruck");
						else if (!fireTruck && securityFlags.Contains("FireTruck")) securityFlags.Remove("FireTruck");

						else if (Tanker && !securityFlags.Contains("Tanker")) securityFlags.Add("Tanker");
						else if (!Tanker && securityFlags.Contains("Tanker")) securityFlags.Remove("Tanker");

						else if (Truck && !securityFlags.Contains("Truck")) securityFlags.Add("Truck");
						else if (!Truck && securityFlags.Contains("Truck")) securityFlags.Remove("Truck");

						else if (Hearse && !securityFlags.Contains("Hearse")) securityFlags.Add("Hearse");
						else if (!Hearse && securityFlags.Contains("Hearse")) securityFlags.Remove("Hearse");

						else if (IceCream && !securityFlags.Contains("IceCream")) securityFlags.Add("IceCream");
						else if (!IceCream && securityFlags.Contains("IceCream")) securityFlags.Remove("IceCream");

						else if (policeCar && !securityFlags.Contains("PoliceCar")) securityFlags.Add("PoliceCar");
						else if (!policeCar && securityFlags.Contains("PoliceCar")) securityFlags.Remove("PoliceCar");
					}

					if (GUI.Button(new Rect(540, upgradeThreeGUICol + 125, GUI.skin.button.fixedWidth, 50), "Purchase")){
						int cost = 0;
						if (securityType == "FL1") {
								cost = 300;
					
						}

						if (securityType == "FL2") {
							cost = security_two_cost + 300; 
						}

						if (securityType == "FL3") {
							cost = security_three_cost + 300;
						}

						if (player.cash >= cost) {
							upgradeChosen = false;
							shopOpen = false;
							Time.timeScale = 1;
							player.cash -= cost;
						}
					}

					if (GUI.Button(new Rect(540, upgradeThreeGUICol + 185, GUI.skin.button.fixedWidth, 50), "Cancel Purchase")){
						securityFlags.Clear();
						clear();
						upgradeChosen = false;
						Time.timeScale = 1;
					}
				}

                if (securityType == "HL1" || securityType == "HL2"  || securityType == "HL3"){
                    GUI.Box(new Rect(0, 0, 0, 0), "Purchase Options");
                    honeyLevel = 1;

                    red    = GUI.Toggle(new Rect(offset, 80, Twidth, Theight), red, "Red");
                    green  = GUI.Toggle(new Rect(offset, 155, Twidth, Theight), green, "Green");
                    blue   = GUI.Toggle(new Rect(offset, 230, Twidth, Theight), blue, "Blue");
                    yellow = GUI.Toggle(new Rect(offset, 305, Twidth, Theight), yellow, "Yellow");

                    //This is to check for what type of color the security gate will look for
                    if (red && !honeyFlags.Contains("Red")) honeyFlags.Add("Red");
                    else if (!red && honeyFlags.Contains("Red")) honeyFlags.Remove("Red");

                    else if (green && !honeyFlags.Contains("Green")) honeyFlags.Add("Green");
                    else if (!green && honeyFlags.Contains("Green")) honeyFlags.Remove("Green");

                    else if (blue && !honeyFlags.Contains("Blue")) honeyFlags.Add("Blue");
                    else if (!blue && honeyFlags.Contains("Blue")) honeyFlags.Remove("Blue");

                    else if (yellow && !honeyFlags.Contains("Yellow")) honeyFlags.Add("Yellow");
                    else if (!yellow && honeyFlags.Contains("Yellow")) honeyFlags.Remove("Yellow");

                    if (securityType == "HL2" || securityType == "HL3"){
                        honeyLevel = 2;

                        small  = GUI.Toggle(new Rect(Twidth + offset, 80, Twidth, Theight), small, "Small");
                        median = GUI.Toggle(new Rect(Twidth + offset, 155, Twidth, Theight), median, "Medium");
                        large  = GUI.Toggle(new Rect(Twidth + offset, 230, Twidth, Theight), large, "Large");

                        //This is to check for what type of color the security gate will look for
                        if (small && !honeyFlags.Contains("Small")) honeyFlags.Add("Small");
                        else if (!small && honeyFlags.Contains("Small")) honeyFlags.Remove("Small");

                        else if (median && !honeyFlags.Contains("Medium")) honeyFlags.Add("Medium");
                        else if (!median && honeyFlags.Contains("Medium")) honeyFlags.Remove("Medium");

                        else if (large && !honeyFlags.Contains("Large")) honeyFlags.Add("Large");
                        else if (!large && honeyFlags.Contains("Large")) honeyFlags.Remove("Large");

                    }

                    if (securityType == "HL3"){
                        honeyLevel = 3;

                        ambulance = GUI.Toggle(new Rect(Twidth * 2 + offset, 80, Twidth, Theight), ambulance, "Ambulance");
                        fireTruck = GUI.Toggle(new Rect(Twidth * 2 + offset, 155, Twidth, Theight), fireTruck, "Fire Truck");
                        Tanker    = GUI.Toggle(new Rect(Twidth * 2 + offset, 230, Twidth, Theight), Tanker, "Oil Truck");
                        Truck     = GUI.Toggle(new Rect(Twidth * 2 + offset, 305, Twidth, Theight), Truck, "Truck");
                        Hearse    = GUI.Toggle(new Rect(Twidth * 2 + offset, 380, Twidth, Theight), Hearse, "Hearse");
                        IceCream  = GUI.Toggle(new Rect(Twidth * 2 + offset, 455, Twidth, Theight), IceCream, "Ice Cream");
                        policeCar = GUI.Toggle(new Rect(Twidth * 2 + offset, 530, Twidth, Theight), policeCar, "Police Car");

                        //This is to check for what type of color the security gate will look for
                        if (ambulance && !honeyFlags.Contains("Ambulance")) honeyFlags.Add("Ambulance");
                        else if (!ambulance && honeyFlags.Contains("Ambulance")) honeyFlags.Remove("Ambulance");

                        else if (fireTruck && !honeyFlags.Contains("FireTruck")) honeyFlags.Add("FireTruck");
                        else if (!fireTruck && honeyFlags.Contains("FireTruck")) honeyFlags.Remove("FireTruck");

                        else if (Tanker && !honeyFlags.Contains("Tanker")) honeyFlags.Add("Tanker");
                        else if (!Tanker && honeyFlags.Contains("Tanker")) honeyFlags.Remove("Tanker");

                        else if (Truck && !honeyFlags.Contains("Truck")) honeyFlags.Add("Truck");
                        else if (!Truck && honeyFlags.Contains("Truck")) honeyFlags.Remove("Truck");

                        else if (Hearse && !honeyFlags.Contains("Hearse")) honeyFlags.Add("Hearse");
                        else if (!Hearse && honeyFlags.Contains("Hearse")) honeyFlags.Remove("Hearse");

                        else if (IceCream && !honeyFlags.Contains("IceCream")) honeyFlags.Add("IceCream");
                        else if (!IceCream && honeyFlags.Contains("IceCream")) honeyFlags.Remove("IceCream");

                        else if (policeCar && !honeyFlags.Contains("PoliceCar")) honeyFlags.Add("PoliceCar");
                        else if (!policeCar && honeyFlags.Contains("PoliceCar")) honeyFlags.Remove("PoliceCar");
                    }

                  if (GUI.Button(new Rect(540, upgradeThreeGUICol + 125, GUI.skin.button.fixedWidth, 50), "Purchase")){
						int cost = 0;
						if (securityType == "HL1") {
                            cost = honey_one_cost + 300;
						}

						if (securityType == "HL2") {
                            cost = honey_two_cost + 300;
						}

						if (securityType == "HL3") {
                            cost = honey_three_cost + 300;
						}

						if (player.cash >= cost) {
							upgradeChosen = false;
							shopOpen = false;
							Time.timeScale = 1;
							player.cash -= cost;
						}
                  }

                 if (GUI.Button(new Rect(540, upgradeThreeGUICol + 185, GUI.skin.button.fixedWidth, 50), "Cancel Purchase")){
                            honeyFlags.Clear();
                            clear();
                            upgradeChosen = false;
                            Time.timeScale = 1;
                 }
               }
			}

			else {
				// This is to contain all of the different buying options
				GUI.Box (new Rect (0, 0, 800, 1000), "Shop");

				// First set of upgrades for the security for the pictures
				GUI.Label (new Rect (upgradeOneGUIRow, upgradeOneGUICol, 128, 128), securityOneImageContainer);
				GUI.Label (new Rect (upgradeOneGUIRow, upgradeTwoGUICol, 128, 128), securityTwoImageContainer);

				// This is the second set of upgrades for the pictures
				GUI.Label (new Rect (upgradeTwoGUIRow, upgradeOneGUICol, 128, 128), securityOneImageContainer);
				GUI.Label (new Rect (upgradeTwoGUIRow, upgradeTwoGUICol, 128, 128), securityTwoImageContainer);

				// This is the third set of upgrades for the pictures
				GUI.Label (new Rect (upgradeThreeGUIRow, upgradeOneGUICol, 128, 128), securityOneImageContainer);
				GUI.Label (new Rect (upgradeThreeGUIRow, upgradeTwoGUICol, 128, 128), securityTwoImageContainer);



				// This button is here for upgrading to security option 1
				if (GUI.Button (new Rect (10, upgradeOneGUICol + 128, GUI.skin.button.fixedWidth, 50), "Firewall One")) {
					securityType = "FL1";
					upgradeChosen = true;
				}

				// This button is here for upgrading to security option 2
				if (GUI.Button (new Rect (10, upgradeTwoGUICol + 128,GUI.skin.button.fixedWidth, 50), "Logger One")) {
					securityType = "HL1";
					upgradeChosen = true;
				}

				// This button is here for upgrading to security option 1
				if (GUI.Button (new Rect (270, upgradeOneGUICol + 128, GUI.skin.button.fixedWidth, 50), "Firewall Two")) {
					securityType = "FL2";
					upgradeChosen = true;
				}

				// This button is here for upgrading to security option 2
				if (GUI.Button (new Rect (270, upgradeTwoGUICol + 128, GUI.skin.button.fixedWidth, 50), "Logger Two")) {
					securityType = "HL2";
					upgradeChosen = true;
				}

				// This button is here for upgrading to security option 1
				if (GUI.Button (new Rect (540, upgradeOneGUICol + 128, GUI.skin.button.fixedWidth, 50), "Firewall Three")) {
					securityType = "FL3";
					upgradeChosen = true;
				}

				// This button is here for upgrading to security option 2
				if (GUI.Button(new Rect(540, upgradeTwoGUICol + 128, GUI.skin.button.fixedWidth, 50), "Logger Three")){
                    securityType = "HL3";
                    upgradeChosen = true;
				}

				// This button is here to close down the shop and place the old GUI buttons on the screen
				if (GUI.Button (new Rect (540, upgradeThreeGUICol + 118, GUI.skin.button.fixedWidth, 50), "Close Shop")) {
					shopOpen = false;
					upgradeChosen = false;
					clear ();
					Time.timeScale = 1;
				}
			}
			// necessary function call for beginGroup
			GUI.EndGroup ();	

		}
	}


	/**
	 * Function that sets the boolean value for shopOpen
	 * @param: Requires a boolean to be set to
	 * @pre: None, requires initialized boolean variable of true or false
	 * @post: Sets shopOpen to if the user clicked on the gui
	 * @algorithm: Sets whatever came in from the parameter to true or false 
	 */ 
	public void setShopOpen(bool set){
		shopOpen = set;
	}


	/**
	 * Function that gets the boolean value for shopOpen
	 * @param: None
	 * @pre: None, requires initialized boolean variable of true or false
	 * @post: None
	 * @algorithm: Gets whatever shopOpen was set to 
	 */ 
	public bool getShopOpen(){
		return shopOpen;
	}

	public string getSecurityType(){
		return securityType;
	}

	public void clear(){
		ambulance = fireTruck = Tanker = Truck = Hearse = IceCream = policeCar = red = green = blue = small = median = yellow =  large = Taxi = false;
		securityType = " ";
	}
}
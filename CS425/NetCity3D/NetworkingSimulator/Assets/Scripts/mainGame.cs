using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using System;
using System.IO;

public class mainGame : MonoBehaviour {
	gameManager gameMgr; // This gets the players information
	shopMenu shopScript; // This gets the information for the shop class, and lets player manipulate their stuff using the shop class
	GUIStyle guiCash;
	GUIStyle guiStyle;
	GUIStyle boxInformation;
    GUIStyle guiLog;

	bool openingShop;  // This is a bool to open up the shop
	public bool placingSecurity; // This is a bool to check for if placing security, this is ok
	public bool showSettings; // This is a bool to check for if it is on show setting

	public Camera myCam; // The camera object
	public GameObject obj; // This is for Save Menu!!!!! TODO
    public GameObject tmpObj; // This is for Save Menu!!!!! TODO

	public float timer = 60; // A timer to calculate how long the user has been playing for
	public string time; // String of the amount of time overall that has passed
	string mins; // String of the amount of minutes that has passed
	string secs; // String of the amount of seconds that has passed


	int highestHP = 0;
	float moneyTimer = 500;
	float moneyTimerReset = 500;
    Dictionary<string, int> moneyHistory = new Dictionary<string, int>();
    public List<Building> buildings = new List<Building>();


    private bool endOfDay = false;
    private float scrollValue;
    public Vector2 scrollPos = Vector2.zero;

	// Use this for initialization
	void Start () {
		// This gets the component known as gameManager and sets it to the variable
		gameMgr = GameObject.Find ("GameObject").GetComponent<gameManager> ();

		// The boolean variable is going to check if the game has started 
        gameMgr.gameIsStarted = true;

		// This is to find the gameObject that holds the shopScript
		shopScript = GameObject.Find("GameObject").GetComponent<shopMenu>();
  
		boxInformation = new GUIStyle ();
		boxInformation.fontSize = 18;
		boxInformation.normal.textColor = Color.green;

        guiLog = new GUIStyle();
        guiLog.fontSize = 18;
        guiLog.normal.textColor = Color.white;
	}
	// Update is called once per frame
    void Update() {
        // This is the timer, calculates the minutes, seconds, and the overall time.
        timer -= Time.deltaTime;
        if (gameMgr.honeyCount != 0)
            moneyTimer -= Time.deltaTime;

        mins = Mathf.Floor(timer / 60).ToString("00");
        secs = Mathf.Floor(timer % 60).ToString("00");
        time = mins + ":" + secs;

        if (moneyTimer < 0 && gameMgr.honeyCount != 0) {
            moneyTimer = moneyTimerReset;
            moneyHistory.Add(time, gameMgr.cash);
        }

        if (timer < 0) {
            endOfDay = true;
            Time.timeScale = 0;
        }

        if (Input.GetKey(KeyCode.Alpha0))
            Time.timeScale = 0;

        if (Input.GetKey(KeyCode.Alpha1))
            Time.timeScale = 1;

        if (Input.GetKey(KeyCode.Alpha2))
            Time.timeScale = 2;

        if (Input.GetKey(KeyCode.Alpha3))
            Time.timeScale = 3;

        if (Input.GetKey(KeyCode.Alpha4))
            Time.timeScale = 4;
    }

	/**
	 * Function to calculate all of the GUI stuff for the main portion of the game
	 * @param: None
	 * @pre: None, requires initialized boolean variables
	 * @post: Loads the required GUI stuff.
	 * 		If user wants to place security, they press g and place a security gate at their mouse' designated spot
	 * 		If user presses Open Shop, the call the function to open up the menu
	 * @algorithm: Checks to see if the user clicked on the gui capabilities in the menu, if so, it launches whatever option that they clicked on 
	 */ 

	void OnGUI(){
			GUI.skin = Resources.Load ("Buttons/ButtonSkin") as GUISkin;
			GUIStyle guiStyle = GUI.skin.GetStyle ("Time");
			GUIStyle guiCash = GUI.skin.GetStyle ("Money");



			Car tempScript;
			// Create a ray object, and have it trace the mousePosition from top down
			Ray ray = myCam.ScreenPointToRay (Input.mousePosition);

			// Create a hit variable that will store the value of whatever it hits
			RaycastHit hitDetected;

			Physics.Raycast (ray, out hitDetected, Mathf.Infinity);

			if (Physics.Raycast (ray, out hitDetected, Mathf.Infinity)) {
			if (hitDetected.collider.tag == "car") {
				// This gets the script from the object that it hits. 
				tempScript = hitDetected.collider.GetComponent <Car> ();
								
				GUI.Box (new Rect (Input.mousePosition.x, Screen.height - Input.mousePosition.y, 150, 150), "Car Information \n");					
				GUI.Label (new Rect (Input.mousePosition.x, Screen.height - Input.mousePosition.y + 20, 100, 100), 
					"Car Type: " + tempScript.carTypeString +
					" \nCar Color: " + tempScript.colorString +
					" \nCar Size : " + tempScript.sizeString, boxInformation);
			} 
			else if (hitDetected.collider.tag == "school"
				|| hitDetected.collider.tag == "Hospatal"
				|| hitDetected.collider.tag == "Bank"  
				|| hitDetected.collider.tag == "Police_station"
				|| hitDetected.collider.tag == "Building2" 
				|| hitDetected.collider.tag == "Petrol" 	
				|| hitDetected.collider.tag == "House") {
				Building tmp;

				tmp = hitDetected.collider.GetComponent<Building> ();
				GUI.Box (new Rect (Input.mousePosition.x, Screen.height - Input.mousePosition.y, 350, 450), "Car Information \n");					
					
				GUI.Label (new Rect (Input.mousePosition.x, Screen.height - Input.mousePosition.y + 20, 300, 300), 
						" Name: " + tmp.name  +
						" \n Life: " + tmp.life, boxInformation);
				}
				
			}

		// This is going to create a label with a rectangle size with the appropriate guiStyle along with the current time after retreiving it from update
		GUI.Label(new Rect((Screen.width / 2)-guiStyle.fixedWidth, 5, 150, 20), time, guiStyle);
        // This displays cash on GUI
        string moneyString = "$" + gameMgr.cash;
        GUI.Label(new Rect(Screen.width/2, 5, 10+moneyString.Length * 23, 20), moneyString, guiCash);
 
		// This outside if statement checks for if the GUI buttons should be shown onto the screen or not.

        if (endOfDay) {

            int ySize = moneyHistory.Count + 1;

            foreach (var hp in gameMgr.honeyPots)
                ySize += hp.carPIDS.Count + 1;

            ySize *= 17;

            scrollPos = GUI.BeginScrollView(new Rect(Screen.width/2 - 300, 100, 600, 600), scrollPos, new Rect(0, 0, 300, ySize) );

            GUI.Label(new Rect(0, 0, 100, 100), "HoneyPot Log", guiLog);
            timer = 60;

            int ypos = 20;
            foreach (KeyValuePair<string, int> kvp in moneyHistory) {
                string temp = "Money Amount: " + kvp.Value + "  Time: " + kvp.Key;
                GUI.Label(new Rect(0, ypos, 100, 100), temp, guiLog);
                ypos += 15;
            }


            ypos += 15;

            foreach (var hp in gameMgr.honeyPots)
                ypos = hp.writeToLog(guiLog, ypos);


            GUI.EndScrollView();

            if (GUI.Button(new Rect(Screen.width - GUI.skin.button.fixedWidth, Screen.height - GUI.skin.button.fixedHeight, GUI.skin.button.fixedWidth, GUI.skin.button.fixedHeight), "Exit")) {
                endOfDay = false;
                Time.timeScale = 1;
                moneyHistory.Clear();
                foreach (var hp in gameMgr.honeyPots) 
                hp.carPIDS.Clear();
            }
        }


		// This checks if the security button was not pressed
		if ( (shopScript.getShopOpen() == false) && (shopScript.getSecurityType() == " ")){
			// This checks if the showSettings button was not pushed
			if (showSettings == false) 	{
						
					// Otherwise, place an interactable GUI button onto the screen called OpenShop
				if (GUI.Button (new Rect (Screen.width - GUI.skin.button.fixedWidth, 5, GUI.skin.button.fixedWidth, GUI.skin.button.fixedHeight), "Open Shop")) {

						// This will set the shopMenu Script to be true, in which it will display the appropriate GUI
						shopScript.setShopOpen (true);
						
					}

					// Or check if the user interacts with the GUI button called settings on the screen
				if (GUI.Button (new Rect (5, 5, GUI.skin.button.fixedWidth, GUI.skin.button.fixedHeight), "Settings")) {
						
						// This is a boolean utilized to open up another set of GUI's for loading and saving, settings
						showSettings = true;							
					}
			}

			// If showSettings is true, then a set of different functionalities will be displayed
			else {
				// Interactable GUI button for quitting the game
				if (GUI.Button (new Rect (Screen.width / 2, (Screen.height / 2) -100, GUI.skin.button.fixedWidth, GUI.skin.button.fixedHeight), "Quit Game")) {
					Application.Quit ();

					// Then quit the game entirely

				}

				// Interactable GUI button for back
				if (GUI.Button (new Rect (Screen.width / 2, (Screen.height / 2), GUI.skin.button.fixedWidth, GUI.skin.button.fixedHeight), "Back ")) {
					
					// Sets this to false, so the setting gui options will not appear
					showSettings = false;					
				}

				if (GUI.Button (new Rect (Screen.width / 2, (Screen.height / 2) +  100, GUI.skin.button.fixedWidth, GUI.skin.button.fixedHeight), "Main Menu ")) {
					// Load the start menu again
                    gameMgr.reset();
					Application.LoadLevel("StartMenu");
				}

				if (GUI.Button (new Rect (Screen.width / 2, (Screen.height / 2) + 200, GUI.skin.button.fixedWidth, GUI.skin.button.fixedHeight), "Save Game ")) {
					// This is used to check if the variable was sucessfully saved
					bool gameSaved = false;

					// Call the function
					gameSaved = gameMgr.saveData();

					// Return back to the menu
					if (gameSaved) {
						showSettings = false;
					} else {
						print ("File corruption");
					}
				}
			}
		}

		if (shopScript.getSecurityType () == "FL1" || shopScript.getSecurityType() == "FL2"  || shopScript.getSecurityType() == "FL3") {
			placingSecurity = true;
			// This will branch into placing a security gate onto the map
			if (placingSecurity == true) {
				// This checks if the user pressed the G key on the keyboard
                if (Input.GetMouseButtonDown(0) && !shopScript.upgradeChosen) {
					// Create a ray object, and have it trace the mousePosition from top down
					Ray vRay = myCam.ScreenPointToRay (Input.mousePosition);

					// Create a hit variable that will store the value of whatever it hits
					RaycastHit hit;
						
					// Cast a raycast from the starting position of the mouse down infinitely
					if (Physics.Raycast (vRay, out hit, Mathf.Infinity)) {

						if (hit.collider.tag == "Terrain") {
					
							// This is a variable that will hold the position of where the hit is detected for the mouse
							Vector3 placePosition;

                            gameMgr.cash -= shopScript.cost ;

							// Store the hit position into the placePosition
							placePosition = hit.point;

							// This will round the x and z variable, not sure if this is needed though since accuracy is much better than inaccuracy for object placement
							placePosition.x = Mathf.Round (placePosition.x);
							placePosition.z = Mathf.Round (placePosition.z);

							// instantiate a tollgate prefab as gameObject into the world (Will be called tollPre(clone), I think
							obj = Instantiate (Resources.Load ("Prefabs/tollPre", typeof(GameObject))) as GameObject;


                            obj.GetComponent<Security>().setList(shopScript.securityFlags);

                            obj.GetComponent<Security>().setMenuBools(shopScript.red, shopScript.green, shopScript.blue, shopScript.yellow,
                                shopScript.small, shopScript.median, shopScript.large, shopScript.ambulance, shopScript.fireTruck, shopScript.Tanker,
                                shopScript.Truck, shopScript.Hearse, shopScript.policeCar, shopScript.IceCream);

							//obj.GetComponent <Security> ().setSecurityType (shopScript.getSecurityType());
							obj.GetComponent <Security> ().level = shopScript.firewallLevel;
							shopScript.securityFlags.Clear ();

							// Change the position of it so it will be placed a little bit above the road level
							obj.transform.position = new Vector3 (placePosition.x, 0.6f, placePosition.z);	
							obj.GetComponent<Security> ().Position = new Vector3(obj.transform.position.x, obj.transform.position.y, obj.transform.position.z);


							// This will add the gate to the list for it to be saved
							gameMgr.securityGates.Add (obj.GetComponent<Security> ());

							// Set the placing security to false, in which it won't let the user keep pressing g for more security gates
							placingSecurity = false;
							shopScript.clear ();
						}
					}
				}	
			}
		}



        if (shopScript.getSecurityType() == "HL1" || shopScript.getSecurityType() == "HL2" || shopScript.getSecurityType() == "HL3")
        {
            placingSecurity = true;

                // This checks if the user pressed the G key on the keyboard
                if (Input.GetMouseButtonDown(0) && !shopScript.upgradeChosen)
                {
                    // Create a ray object, and have it trace the mousePosition from top down
                    Ray vRay = myCam.ScreenPointToRay(Input.mousePosition);

                    // Create a hit variable that will store the value of whatever it hits
                    RaycastHit hit;

                    // Cast a raycast from the starting position of the mouse down infinitely
                    if (Physics.Raycast(vRay, out hit, Mathf.Infinity))
                    {
                        if (hit.collider.tag == "Terrain")
                        {

                            // This is a variable that will hold the position of where the hit is detected for the mouse
                            Vector3 placePosition;

                            // Store the hit position into the placePosition
                            placePosition = hit.point;

                            // This will round the x and z variable, not sure if this is needed though since accuracy is much better than inaccuracy for object placement
                            placePosition.x = Mathf.Round(placePosition.x);
                            placePosition.z = Mathf.Round(placePosition.z);

                            // instantiate a tollgate prefab as gameObject into the world (Will be called tollPre(clone), I think
                            obj = Instantiate(Resources.Load("Prefabs/HoneySpoon", typeof(GameObject))) as GameObject;

                            obj.GetComponent<HoneyPot>().setList(shopScript.honeyFlags);
                            obj.GetComponent<HoneyPot>().setLevel(shopScript.honeyLevel);
                            obj.GetComponent<HoneyPot>().setMenuBools(shopScript.red, shopScript.green, shopScript.blue, shopScript.yellow,
                                shopScript.small, shopScript.median, shopScript.large, shopScript.ambulance, shopScript.fireTruck, shopScript.Tanker,
                                shopScript.Truck, shopScript.Hearse, shopScript.policeCar, shopScript.IceCream);

                            // Change the position of it so it will be placed a little bit above the road level
                            obj.transform.position = new Vector3(placePosition.x, 0.6f, placePosition.z);


							obj.GetComponent<HoneyPot> ().Position = new Vector3(obj.transform.position.x, obj.transform.position.y, obj.transform.position.z);

                            // Set the placing security to false, in which it won't let the user keep pressing g for more security gates
                            gameMgr.honeyPots.Add( obj.GetComponent<HoneyPot>() );
                            placingSecurity = false;
                            shopScript.clear();
                            shopScript.honeyFlags.Clear();

						    if (obj.GetComponent<HoneyPot> ().level > highestHP) {
							   highestHP = obj.GetComponent<HoneyPot> ().level;
                               if (moneyTimer > 29 && obj.GetComponent<HoneyPot>().level == 1){
                                   moneyTimer = moneyTimerReset = 29;
                               }

                               if (moneyTimer > 20 && obj.GetComponent<HoneyPot>().level == 2) {
								    moneyTimer = moneyTimerReset = 20;
                               }

                               if (moneyTimer > 10 && obj.GetComponent<HoneyPot>().level == 3) {
								    moneyTimer = moneyTimerReset = 10;  
                               }
						     }

                        }
                    }
                }
        }

		if (shopScript.getShopOpen () == true) {
			Time.timeScale = 0;
		}
	}
}



using UnityEngine;
using System.Collections;

public class LoaderUser : MonoBehaviour {
	public string name = "";
	public string password = "";

	GameObject playerMemory;
	gameManager playerScript;

	// Use this for initialization
	void Start () {
		//to access playerManager which is not destroyed throughout scenes
		playerMemory = GameObject.Find ("GameObject");
		playerScript = playerMemory.GetComponent<gameManager> ();	
	}
	
	// Update is called once per frame
	void Update () {
	
	}

	//sets up buttons for loading user
	void OnGUI()
	{
		float width = 300.0f;
		float height = 35.0f;
		GUI.skin = Resources.Load ("Buttons/ButtonSkin") as GUISkin;
		//set color and create label
		GUI.contentColor = Color.black;
		GUI.Label(new Rect ((Screen.width / 2) - width / 2, (Screen.height / 4) - 50, 400, height), "Please Insert Username");
		
		GUI.Label(new Rect ((Screen.width / 2) - width / 2, (Screen.height / 4) + (2 * height) + 5 - 50, 400, height), "Please Insert Password");

		//create textfields to insert username and password
		GUI.contentColor = Color.white;
		name = GUI.TextField(new Rect ((Screen.width / 2) - width / 2, (Screen.height / 4) + height + 5 - 50, width, height), name.Trim (), 30);

		password = GUI.PasswordField(new Rect ((Screen.width / 2) - width / 2, (Screen.height / 4) + (3 * height) + 5 - 50, width, height), password, "*"[0], 30);

		GUI.color= Color.white;
		
		// This button is to load the profile
		if (GUI.Button (new Rect (Screen.width / 2, (Screen.height / 2) + 75, 100, 50), "Find profile")) {
			playerScript.setPassword(password);
			playerScript.setUserName (name);
			// Load tutorial 01, but then make sure that the game manager realizes that a user is loaded
			Application.LoadLevel("Tutorial01");

			playerScript.setUserFound (true);
		}

		// This button is to return to mainMenu
		if (GUI.Button (new Rect ((Screen.width )/10, (Screen.height )/10 , 100, 50), "Main Menu")) {
			Application.LoadLevel("StartMenu");

		}
	}

}

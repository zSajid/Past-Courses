using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class tutorials : MonoBehaviour {
	public MovieTexture[] tutTextures;
	public string[] tutStrings;
	public int currentTut;



	// Use this for initialization
	void Start () {
		tutStrings[0]= "1. Welcome to NetCity 3D. First off our city layout has 3 entrances where traffic spawns from.This entrances need to be monitored to protect the city from certain types of cars.Your job is to find out which types of cars are good and which are bad.";
		tutStrings[1] = "2. As we can see the vehicles are destroyed once they reach their desitnation. At that time our amount of money either increases or decreases on the top middle of the screen. What we want to to reach $5000 to win. We will lose if it reaches $0.";
		tutStrings [2] = "3. We can zoom in with the camera by pressing 'R' and zoom out by clicking 'F'. Then we can move it in the corresponding directions by using the 'W''A''S''D' keys. And if you get lost you can click the space bar and it will take you back to the neutral spot.";
		tutStrings [3] = "4. By hovering the mouse over vehicles we can see some information like its size, color, and type of vehicle. When hovering over the buildings we can see the name of the building and the Life points of the building. If enough bad vehicles reach a certain vehicle the points may become 0.";
		tutStrings [4] = "5. If we open our Shop which is the top right button we see the tools we can use to protect our city from bad traffic. First we have a Firewall that destroys vehicles that fit its destroy criteria. Next is a Logger that logs certain vehicles that pass near its path.";
		tutStrings [5] = "6. When we click the Firewall One we see that it isn't that complex and only has colors. As the levels go up we can see the specificness of the types of vehicle the firewall will destroy. Once the rules are set we Purchase and right click where on the map we would like to place the firewall. After we can also change the rules by left-clicking on it and we can also move it by right clicking on it.";
		tutStrings [6] = "7. When we click on the Logger we also have different levels with the same idea as the Firewalls. We can also move and change the rules the same way as the firewall."; 
		tutStrings [7] = "8. When the timer reaches 0 the Logger log will be presented on the screen. It will demonstrate the revenue at different times of the day. For each corresponding levels its every 1 minute, 30 seconds, and 15 seconds. Then it will also log the vehicles that passed by it. You start the next day by clicking Exit on the bottom left.";
		tutStrings [8] = "9. We can also speed up the day by clicking the numbers 1-4. If 4 is clicked it will speed up 4 times as fast. Also to pause we can click 0.";

	}
	
	// Update is called once per frame
	void Update () {
	
	}

	void OnGUI()
	{

		GUI.skin = Resources.Load ("Buttons/ShopSkin") as GUISkin;
		GUI.skin.box.fixedWidth = 800;
		GUI.skin.box.fixedHeight = 3*Screen.height/4;
		GUI.Box(new Rect((Screen.width/2)-(GUI.skin.box.fixedWidth/2), (Screen.height/2)-(GUI.skin.box.fixedHeight/2), 0, 0), "Tutorials");
		GUI.skin = Resources.Load ("Buttons/ButtonSkin") as GUISkin;
		GUI.skin.box.fixedWidth = 500;
		GUI.skin.box.fixedHeight = 250;
		GUI.Box (new Rect ((Screen.width / 2) - (GUI.skin.box.fixedWidth / 2), Screen.height/6 +5, 0, 0),tutTextures[currentTut] as MovieTexture);
		tutTextures[currentTut].Play();
		tutTextures[currentTut].loop = true;
		GUI.skin = Resources.Load ("Buttons/TutorialSkin") as GUISkin;
		GUI.TextField (new Rect ((Screen.width / 2) - (GUI.skin.box.fixedWidth / 2),Screen.height/6+250+7, 0, 0), tutStrings [currentTut]);
		// This button is to go to skip tutorials and start game
		if (GUI.Button (new Rect ((Screen.width/2)-GUI.skin.button.fixedWidth/2, (3*Screen.height/4 ) +90, GUI.skin.button.fixedWidth, GUI.skin.button.fixedHeight), "Skip Tutorials")) {
			Application.LoadLevel("SelectionMenu");			
		}

		// This button is to go to start game
        if (GUI.Button(new Rect((Screen.width / 2) + GUI.skin.button.fixedWidth / 2, (3 * Screen.height / 4) + 90, GUI.skin.button.fixedWidth, GUI.skin.button.fixedHeight), "Next")) {
			currentTut++;
			currentTut %= tutTextures.Length;
			if(tutTextures[currentTut].isPlaying){
				tutTextures[currentTut].Stop ();
			}
		}
	}
}

using UnityEngine;
using System.Collections;

public class selectionScript : MonoBehaviour {

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}


	
	void OnGUI()
	{
		
		GUI.skin = Resources.Load ("Buttons/ButtonSkin") as GUISkin;
		// This button is to go to first tutorial
		if (GUI.Button (new Rect ((Screen.width/2)-GUI.skin.button.fixedWidth/2, (Screen.height/2 ) , GUI.skin.button.fixedWidth, GUI.skin.button.fixedHeight), "Start Game")) {
			
			Application.LoadLevel("tutorial01");			
		}

	}
}

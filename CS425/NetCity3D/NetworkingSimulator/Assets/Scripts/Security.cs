using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using System;
using System.IO;

public class Security : MonoBehaviour {
	public Vector3 Position;
	Animator animation;
	bool objectDetected;

	public List<string> Keys = new List<string>();

	// This is the set of colors that it can detect
	public bool red;
	public bool green;
	public bool blue;
	public bool yellow;

	// This is the set of sizes that it can detect
	public bool small;
	public bool medium;
	public bool large;

	// This is the type of cars the security gate has to detect and destroy
	public bool ambulance;
	public bool fireTruck;
	public bool Tanker;
	public bool Truck;
	public bool Hearse;
	public bool IceCream;
	public bool policeCar;
	public bool taxi;
	public bool upgrade = false;

	public List<string> securityFlags = new List<string>();
	public int level; // This is the level
	public Camera myCam; // The camera object


	// Use this for initialization
	void Start () {
		myCam = GameObject.Find("Main Camera").GetComponent<Camera>();
		animation = GetComponent<Animator> ();
		objectDetected = false;
	}

	void OnMouseOver(){
		if (Input.GetMouseButtonDown (1)) 
			upgrade = true;

        if (Input.GetKey(KeyCode.LeftShift))
            transform.Rotate(0,90,0);
	}

	// Update is called once per frame
    void Update () {
	}


    void OnCollisionEnter(Collision col) {
     // Check if it is security type 1, 2, or 3
     if (col.gameObject.tag == "car") {
        Car colCar = col.gameObject.GetComponent<Car>();
            if (securityFlags.Contains(colCar.colorString) || securityFlags.Contains(colCar.carTypeString) || securityFlags.Contains(colCar.sizeString))
                        Destroy(col.gameObject);
     }

   }


	void OnMouseDrag(){

		Ray vRay = myCam.ScreenPointToRay(Input.mousePosition);

		// Create a hit variable that will store the value of whatever it hits
		RaycastHit hit;

		// Cast a raycast from the starting position of the mouse down infinitely
		if (Physics.Raycast(vRay, out hit, Mathf.Infinity)){
			if (hit.collider.tag == "Terrain" || hit.collider.tag == "tollPre") {
				if(hit.point.x > 0 && hit.point.x < 300 && hit.point.z > 0 && hit.point.z < 300){
					// This is a variable that will hold the position of where the hit is detected for the mouse
					Vector3 placePosition;

					// Store the hit position into the placePosition
					placePosition = hit.point;

					// This will round the x and z variable, not sure if this is needed though since accuracy is much better than inaccuracy for object placement
					placePosition.x = Mathf.Round(placePosition.x);
					placePosition.z = Mathf.Round(placePosition.z);

					// Change the position of it so it will be placed a little bit above the road level
					transform.position = new Vector3(placePosition.x, 0.6f, placePosition.z);

					// Update the position in terms of the class variable
					Position = new Vector3 (transform.position.x, transform.position.y, transform.position.z);
				}
			}

		}    
	}

	void OnGUI(){

		GUI.skin = Resources.Load ("Buttons/ShopSkin") as GUISkin;
		GUIStyle guiStyle = GUI.skin.GetStyle ("Shop");

		int offset = 360;
		float Twidth = GUI.skin.toggle.fixedWidth;
		float Theight = 30f;

		if (upgrade == true){
			Time.timeScale = 0;
			GUI.Box(new Rect(350, 100, 700, 700), "Upgrade Options");


			red = GUI.Toggle(new Rect(offset, 140, Twidth, Theight), red, "Red");
			green = GUI.Toggle(new Rect(offset, 215, Twidth, Theight), green, "Green");
			blue = GUI.Toggle(new Rect(offset, 290, Twidth, Theight), blue, "Blue");
			yellow = GUI.Toggle(new Rect(offset, 365, Twidth, Theight), yellow, "Yellow");

			//This is to check for what type of color the security gate will look for
			if (red && !securityFlags.Contains("Red")) securityFlags.Add("Red"); 
			else if (!red && securityFlags.Contains("Red")) securityFlags.Remove("Red");

			else if (green && !securityFlags.Contains("Green")) securityFlags.Add("Green"); 
			else if (!green && securityFlags.Contains("Green")) securityFlags.Remove("Green");

			else if (blue && !securityFlags.Contains("Blue"))  securityFlags.Add("Blue");
			else if (!blue && securityFlags.Contains("Blue"))  securityFlags.Remove("Blue"); 

			else if (yellow && !securityFlags.Contains("Yellow"))  securityFlags.Add("Yellow");
			else if (!yellow && securityFlags.Contains("Yellow"))  securityFlags.Remove("Yellow");


			if (level >= 2){

				small = GUI.Toggle(new Rect(Twidth + offset, 140, Twidth, Theight), small, "Small");
				medium = GUI.Toggle(new Rect(Twidth + offset, 215, Twidth, Theight), medium, "Medium");
				large = GUI.Toggle(new Rect(Twidth + offset, 290, Twidth, Theight), large, "Large");

				if (small && !securityFlags.Contains("Small"))  securityFlags.Add("Small"); 
				else if (!small && securityFlags.Contains("Small"))  securityFlags.Remove("Small");

				else if (medium && !securityFlags.Contains("Medium"))  securityFlags.Add("Medium"); 
				else if (!medium && securityFlags.Contains("Medium"))  securityFlags.Remove("Medium"); 

				else if (large && !securityFlags.Contains("Large"))  securityFlags.Add("Large");
				else if (!large && securityFlags.Contains("Large"))  securityFlags.Remove("Large");
			}



			if (level >= 3){
				ambulance = GUI.Toggle(new Rect(Twidth * 2 + offset, 140, Twidth, Theight), ambulance, "Ambulance");
				fireTruck = GUI.Toggle(new Rect(Twidth * 2 + offset, 215, Twidth, Theight), fireTruck, "Fire Truck");
				Tanker = GUI.Toggle(new Rect(Twidth * 2 + offset, 290, Twidth, Theight), Tanker, "Oil Truck");
				Truck = GUI.Toggle(new Rect(Twidth * 2 + offset, 365, Twidth, Theight), Truck, "Truck");
				Hearse = GUI.Toggle(new Rect(Twidth * 2 + offset, 440, Twidth, Theight), Hearse, "Hearse");
				IceCream = GUI.Toggle(new Rect(Twidth * 2 + offset, 515, Twidth, Theight), IceCream, "Ice Cream");
				policeCar = GUI.Toggle(new Rect(Twidth * 2 + offset, 590, Twidth, Theight), policeCar, "Police Car");


				if (ambulance && !securityFlags.Contains("Ambulance")) securityFlags.Add("Ambulance"); 
				else if (!ambulance && securityFlags.Contains("Ambulance")) securityFlags.Remove("Ambulance");

				else if (fireTruck && !securityFlags.Contains("FireTruck"))  securityFlags.Add("FireTruck");
				else if (!fireTruck && securityFlags.Contains("FireTruck"))  securityFlags.Remove("FireTruck");

				else if (Tanker && !securityFlags.Contains("Tanker"))  securityFlags.Add("Tanker");
				else if (!Tanker && securityFlags.Contains("Tanker"))  securityFlags.Remove("Tanker");

				else if (Truck && !securityFlags.Contains("Truck"))  securityFlags.Add("Truck");
				else if (!Truck && securityFlags.Contains("Truck"))  securityFlags.Remove("Truck");

				else if (Hearse && !securityFlags.Contains("Hearse"))  securityFlags.Add("Hearse");
				else if (!Hearse && securityFlags.Contains("Hearse"))  securityFlags.Remove("Hearse"); 

				else if (IceCream && !securityFlags.Contains("IceCream"))  securityFlags.Add("IceCream");
				else if (!IceCream && securityFlags.Contains("IceCream"))  securityFlags.Remove("IceCream"); 

				else if (policeCar && !securityFlags.Contains("PoliceCar"))  securityFlags.Add("PoliceCar");
				else if (!policeCar && securityFlags.Contains("PoliceCar"))  securityFlags.Remove("PoliceCar"); 
			}

			if (GUI.Button(new Rect(offset, 550, GUI.skin.button.fixedWidth, 50), "Change")){
				upgrade = false;
				Time.timeScale = 1;
			}

			if (GUI.Button(new Rect(offset, 650, GUI.skin.button.fixedWidth, 50), "Cancel Change")){
				//clear();
				upgrade = false;
				Time.timeScale = 1;
			}
		}
	}
	public Vector3 getPosition(){
		return Position;
	}

	public void setPosition(Vector3 inVect){
		Position = inVect;
	}


    public void setMenuBools(bool r, bool g, bool b, bool y, bool s, bool m, bool l, bool a, bool f, bool ta, bool tr, bool h, bool p, bool i) {
        red = r; blue = b; yellow = y; green = g;
        small = s; medium = m; large = l;
        ambulance = a; fireTruck = f; Tanker = ta; Truck = tr;
        Hearse = h; policeCar = p; IceCream = i;
    }

    public void setList(List<string> purchasedList) {
        securityFlags.AddRange(purchasedList);
    }
}



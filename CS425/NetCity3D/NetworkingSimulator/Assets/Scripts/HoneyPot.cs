using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using System;
using System.IO;

public class HoneyPot : MonoBehaviour {
  public Vector3 Position;

  gameManager gameMgr;
  mainGame main;
  public Dictionary<int, Car> carPIDS = new Dictionary<int, Car>();
  public List<string> Keys = new List<string>();

  public int level = 1;
	public  int PID;

	public bool upgrade = false;
	public bool red = false;
	public bool blue = false;
	public bool yellow = false;
	public bool green = false;
	public bool small = false;
	public bool median = false;
	public bool large = false;
	public bool ambulance = false;
	public bool fireTruck = false;
	public bool Tanker = false;
	public bool Truck = false;
	public bool Hearse = false;
	public bool policeCar = false;
	public bool IceCream = false;
	public  bool first = true;

  public Camera myCam; // The camera object

	// Use this for initialization
	void Start () {
      gameMgr = GameObject.Find("GameObject").GetComponent<gameManager>();
      main = GameObject.Find("Main Camera").GetComponent<mainGame>();
      PID = gameMgr.honeyCount++;
      myCam = GameObject.Find("Main Camera").GetComponent<Camera>();

	}
	
	// Update is called once per frame
	void Update () {
	}

    void OnMouseOver(){
        if ( Input.GetMouseButtonDown(1))
        upgrade = true;
    }

	void OnCollisionEnter(Collision col){
        if( col.gameObject.tag == "car" ){
           Car colCar = col.gameObject.GetComponent<Car>();

              if (Keys.Contains(colCar.colorString) || Keys.Contains(colCar.carTypeString) || Keys.Contains(colCar.sizeString) ){

                if (!carPIDS.ContainsKey(colCar.carPID)){
                    colCar.honeyPotIn = main.time;
                    carPIDS.Add(colCar.carPID, colCar);
                }
             }
        }
	}


    void OnMouseDrag(){

            Ray vRay = myCam.ScreenPointToRay(Input.mousePosition);

            // Create a hit variable that will store the value of whatever it hits
            RaycastHit hit;

            // Cast a raycast from the starting position of the mouse down infinitely
            if (Physics.Raycast(vRay, out hit, Mathf.Infinity)){
                if (hit.collider.tag == "Terrain" || hit.collider.tag == "Honey") {
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

    public void setList(List<string> purchasedList){
        Keys.AddRange(purchasedList);
    }

    public void setLevel(int l){
        level = l;
    }

    public void setMenuBools(bool r, bool g, bool b, bool y, bool s, bool m, bool l, bool a, bool f, bool ta, bool tr, bool h, bool p, bool i){
      red = r;  blue = b; yellow = y; green = g;
      small = s; median = m; large = l;
      ambulance = a; fireTruck = f; Tanker = ta; Truck = tr;
      Hearse = h; policeCar = p; IceCream = i;
    }

    public int writeToLog(GUIStyle gs, int pos){

        GUI.Label(new Rect(0, pos, 100, 100),"Log for HoneyPot " + PID + "(Level" + level + "):", gs);
        pos += 15;

        foreach (KeyValuePair<int, Car> kvp in carPIDS){
            string temp = "";

            if (level == 1)
                temp = "Car Color: " + kvp.Value.colorString  + "Time: " + kvp.Value.honeyPotIn;

            if (level == 2)
                temp = "Car Color:" + kvp.Value.colorString + "Car Size: " + kvp.Value.sizeString + "Time: " + kvp.Value.honeyPotIn;
            
            if (level == 3)
                temp = "Car Color: " + kvp.Value.colorString + "Car Size: " + kvp.Value.sizeString + "Car Type: " + kvp.Value.carTypeString + "Time: " + kvp.Value.honeyPotIn;

            GUI.Label(new Rect(0, pos, 100, 100), temp, gs);

            pos += 15;
        }
        pos += 15;
        return pos;
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
                if (red && !Keys.Contains("Red")) Keys.Add("Red"); 
                else if (!red && Keys.Contains("Red")) Keys.Remove("Red");

                else if (green && !Keys.Contains("Green")) Keys.Add("Green"); 
                else if (!green && Keys.Contains("Green")) Keys.Remove("Green");

                else if (blue && !Keys.Contains("Blue"))  Keys.Add("Blue");
                else if (!blue && Keys.Contains("Blue"))  Keys.Remove("Blue"); 

                else if (yellow && !Keys.Contains("Yellow"))  Keys.Add("Yellow");
                else if (!yellow && Keys.Contains("Yellow"))  Keys.Remove("Yellow");


            if (level >= 2){

                small = GUI.Toggle(new Rect(Twidth + offset, 140, Twidth, Theight), small, "Small");
                median = GUI.Toggle(new Rect(Twidth + offset, 215, Twidth, Theight), median, "Meduim");
                large = GUI.Toggle(new Rect(Twidth + offset, 290, Twidth, Theight), large, "Large");

                if (small && !Keys.Contains("Small"))  Keys.Add("Small"); 
                else if (!small && Keys.Contains("Small"))  Keys.Remove("Small");

                else if (median && !Keys.Contains("Medium"))  Keys.Add("Medium"); 
                else if (!median && Keys.Contains("Medium"))  Keys.Remove("Medium"); 

                else if (large && !Keys.Contains("Large"))  Keys.Add("Large");
                else if (!large && Keys.Contains("Large"))  Keys.Remove("Large");
            }



            if (level >= 3){
                ambulance = GUI.Toggle(new Rect(Twidth * 2 + offset, 140, Twidth, Theight), ambulance, "Ambulance");
                fireTruck = GUI.Toggle(new Rect(Twidth * 2 + offset, 215, Twidth, Theight), fireTruck, "Fire Truck");
                Tanker = GUI.Toggle(new Rect(Twidth * 2 + offset, 290, Twidth, Theight), Tanker, "Oil Truck");
                Truck = GUI.Toggle(new Rect(Twidth * 2 + offset, 365, Twidth, Theight), Truck, "Truck");
                Hearse = GUI.Toggle(new Rect(Twidth * 2 + offset, 440, Twidth, Theight), Hearse, "Hearse");
                IceCream = GUI.Toggle(new Rect(Twidth * 2 + offset, 515, Twidth, Theight), IceCream, "Ice Cream");
                policeCar = GUI.Toggle(new Rect(Twidth * 2 + offset, 590, Twidth, Theight), policeCar, "Police Car");
 

                if (ambulance && !Keys.Contains("Ambulance")) Keys.Add("Ambulance"); 
                else if (!ambulance && Keys.Contains("Ambulance")) Keys.Remove("Ambulance");

                else if (fireTruck && !Keys.Contains("FireTruck"))  Keys.Add("FireTruck");
                else if (!fireTruck && Keys.Contains("FireTruck"))  Keys.Remove("FireTruck");

                else if (Tanker && !Keys.Contains("Tanker"))  Keys.Add("Tanker");
                else if (!Tanker && Keys.Contains("Tanker"))  Keys.Remove("Tanker");

                else if (Truck && !Keys.Contains("Truck"))  Keys.Add("Truck");
                else if (!Truck && Keys.Contains("Truck"))  Keys.Remove("Truck");

                else if (Hearse && !Keys.Contains("Hearse"))  Keys.Add("Hearse");
                else if (!Hearse && Keys.Contains("Hearse"))  Keys.Remove("Hearse"); 

                else if (IceCream && !Keys.Contains("IceCream"))  Keys.Add("IceCream");
                else if (!IceCream && Keys.Contains("IceCream"))  Keys.Remove("IceCream"); 

                else if (policeCar && !Keys.Contains("PoliceCar"))  Keys.Add("PoliceCar");
                else if (!policeCar && Keys.Contains("PoliceCar"))  Keys.Remove("PoliceCar"); 
            }

            if (GUI.Button(new Rect(offset, 550, GUI.skin.button.fixedWidth, 50), "Purchase")){
                    upgrade = false;
                    Time.timeScale = 1;
            }

            if (GUI.Button(new Rect(offset, 650, GUI.skin.button.fixedWidth, 50), "Cancel Purchase")){
                    //clear();
                    upgrade = false;
                    Time.timeScale = 1;

                }
        }
    }
}

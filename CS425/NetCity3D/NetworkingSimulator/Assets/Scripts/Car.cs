using UnityEngine;
using System.Collections;

public class Car : MonoBehaviour {
	gameManager gameMgr;

	//WavePoint Stuff
	public Transform[] wayPointList;
	public int currentWayPoint = 0;
	public Transform targetWayPoint;

    //Car Details
    public string colorString;
    public string sizeString;
    public string carTypeString;

	public int route;
    public int carColor;
	public float speed = 10.0f;
    public int carPID;

	public Vector3 position; // The position of the vehicle
    public string honeyPotIn;

	// Use this for initialization
	void Awake () {
        gameMgr = GameObject.Find("GameObject").GetComponent<gameManager>();	

		//Random Path for now
		if (gameMgr.carStartIndex == 0) {
			route = Random.Range (0, 7);
		} 
		else if (gameMgr.carStartIndex == 1) {
			route = Random.Range (7, 14);
		} 
		else {
			route = Random.Range(14,21);
		}

		carColor = Random.Range(0,4);

		carTypeString = gameMgr.carTypeDict[gameMgr.carType];
        sizeString = gameMgr.carSizeDict[gameMgr.carType];
        colorString = gameMgr.carColorDict[carColor];
        carPID = gameMgr.count;
		setWavePoints (route);
        targetWayPoint = wayPointList[currentWayPoint];

        gameObject.GetComponent<Renderer>().material.color = gameMgr.colorArray[carColor];


        //if(gameObject.GetComponent<Car>().carTypeString != "PoliceCar")
        //gameObject.GetComponent<Renderer>().material = Resources.Load("Materials/" + colorString + carTypeString) as Material;

        gameMgr.activeCars.Add(gameObject.GetComponent<Car>());
	}
	
	// Update is called once per frame
	void Update () {
		
		if (currentWayPoint < this.wayPointList.Length)
			drive();
	}

	//Called when two objects touch
	void OnCollisionEnter(Collision col){

	}

	void drive(){
			transform.forward = Vector3.RotateTowards (transform.forward, targetWayPoint.position - transform.position, speed * Time.deltaTime, 0.0f);
			transform.position = Vector3.MoveTowards (transform.position, targetWayPoint.position, speed * Time.deltaTime);
			
			if (transform.position == targetWayPoint.position)
				currentWayPoint++;
			
			if (currentWayPoint < this.wayPointList.Length)
				targetWayPoint = wayPointList [currentWayPoint];
		
	} 

	void setWavePoints(int ro){
  
		switch( ro ){
			//startPos0
            case 0:
                 wayPointList = new Transform[4];
  			     wayPointList[0] = GameObject.Find ("WayPoint1").transform;
  			     wayPointList[1] = GameObject.Find ("WayPoint2").transform;
  			     wayPointList[2] = GameObject.Find ("WayPoint3").transform;
 			     wayPointList[3] = GameObject.Find ("BankPoint").transform;
                 break;

            case 1:
                 wayPointList = new Transform[4];
                 wayPointList[0] = GameObject.Find("WayPoint1").transform;
                 wayPointList[1] = GameObject.Find("WayPoint5").transform;
                 wayPointList[2] = GameObject.Find("WayPoint6").transform;
                 wayPointList[3] = GameObject.Find("HousePoint").transform;
                 break;

            case 2:
 			    wayPointList = new Transform[3];
 			    wayPointList[0] = GameObject.Find ("WayPoint1").transform;
 			    wayPointList[1] = GameObject.Find ("WayPoint8").transform;
 		    	wayPointList[2] = GameObject.Find ("PolicePoint").transform;
 		    	break;
 
 		    case 3:
 		    	wayPointList = new Transform[3];
                wayPointList[0] = GameObject.Find ("WayPoint1").transform;
  			    wayPointList[1] = GameObject.Find ("WayPoint10").transform;
                wayPointList[2] = GameObject.Find ("StorePoint").transform;
 		    	break;
 
 	    	case 4:
 		    	wayPointList = new Transform[2];
 		    	wayPointList[0] = GameObject.Find ("WayPoint1").transform;
 			    wayPointList[1] = GameObject.Find ("PetrolPoint").transform;
                break;
  
 	    	case 5:
 		    	wayPointList = new Transform[4];
 		    	wayPointList[0] = GameObject.Find ("WayPoint1").transform;
 		    	wayPointList[1] = GameObject.Find ("WayPoint5").transform;
 		    	wayPointList[2] = GameObject.Find ("WayPoint16").transform;
 		    	wayPointList[3] = GameObject.Find ("SchoolPoint").transform;
 		    	break;
 
 		    case 6:
 			    wayPointList = new Transform[4];
                wayPointList[0] = GameObject.Find ("WayPoint1").transform;
  			    wayPointList[1] = GameObject.Find ("WayPoint2").transform;
 		    	wayPointList[2] = GameObject.Find ("WayPoint14").transform;
 		    	wayPointList[3] = GameObject.Find ("HospitalPoint").transform;
                break;
			//startPos1
			case 7:
				wayPointList = new Transform[5];
				wayPointList[0] = GameObject.Find ("WayPoint17").transform;
				wayPointList[1] = GameObject.Find ("WayPoint18").transform;
				wayPointList[2] = GameObject.Find ("WayPoint19").transform;
				wayPointList[3] = GameObject.Find ("WayPoint20").transform;
				wayPointList[4] = GameObject.Find ("BankPoint2").transform;
				break;

			case 8:
				wayPointList = new Transform[3];
				wayPointList[0] = GameObject.Find("WayPoint17").transform;
				wayPointList[1] = GameObject.Find("WayPoint18").transform;
				wayPointList[2] = GameObject.Find("HousePoint2").transform;
				break;

			case 9:
				wayPointList = new Transform[6];
				wayPointList[0] = GameObject.Find ("WayPoint17").transform;
				wayPointList[1] = GameObject.Find ("WayPoint23").transform;
				wayPointList[2] = GameObject.Find ("WayPoint24").transform;
				wayPointList[3] = GameObject.Find ("WayPoint25").transform;
				wayPointList[4] = GameObject.Find ("WayPoint26").transform;
				wayPointList[5] = GameObject.Find ("PolicePoint").transform;
				break;
				
			case 10:
				wayPointList = new Transform[6];
				wayPointList[0] = GameObject.Find ("WayPoint17").transform;
				wayPointList[1] = GameObject.Find ("WayPoint23").transform;
				wayPointList[2] = GameObject.Find ("WayPoint24").transform;
				wayPointList[3] = GameObject.Find ("WayPoint25").transform;
				wayPointList[4] = GameObject.Find ("WayPoint27").transform;
				wayPointList[5] = GameObject.Find ("StorePoint2").transform;
				break;
				
			case 11:
				wayPointList = new Transform[5];
				wayPointList[0] = GameObject.Find ("WayPoint17").transform;
				wayPointList[1] = GameObject.Find ("WayPoint23").transform;
				wayPointList[2] = GameObject.Find ("WayPoint24").transform;
				wayPointList[3] = GameObject.Find ("WayPoint29").transform;
				wayPointList[4] = GameObject.Find ("PetrolPoint2").transform;
				break;
				
			case 12:
				wayPointList = new Transform[3];
				wayPointList[0] = GameObject.Find ("WayPoint17").transform;
				wayPointList[1] = GameObject.Find ("WayPoint23").transform;
				wayPointList[2] = GameObject.Find ("SchoolPoint2").transform;
				break;
				
			case 13:
				wayPointList = new Transform[5];
				wayPointList[0] = GameObject.Find ("WayPoint17").transform;
				wayPointList[1] = GameObject.Find ("WayPoint23").transform;
				wayPointList[2] = GameObject.Find ("WayPoint24").transform;
				wayPointList[3] = GameObject.Find ("WayPoint32").transform;
				wayPointList[4] = GameObject.Find ("HospitalPoint").transform;
				break;

			//startPos2
			case 14:
				wayPointList = new Transform[3];
				wayPointList[0] = GameObject.Find ("WayPoint33").transform;
				wayPointList[1] = GameObject.Find ("WayPoint34").transform;
				wayPointList[2] = GameObject.Find ("BankPoint").transform;
				break;
				
			case 15:
				wayPointList = new Transform[5];
				wayPointList[0] = GameObject.Find("WayPoint33").transform;
				wayPointList[1] = GameObject.Find("WayPoint34").transform;
				wayPointList[2] = GameObject.Find("WayPoint35").transform;
				wayPointList[3] = GameObject.Find("WayPoint36").transform;
				wayPointList[4] = GameObject.Find("HousePoint").transform;
				break;
				
			case 16:
				wayPointList = new Transform[6];
				wayPointList[0] = GameObject.Find ("WayPoint33").transform;
				wayPointList[1] = GameObject.Find ("WayPoint37").transform;
				wayPointList[2] = GameObject.Find ("WayPoint38").transform;
				wayPointList[3] = GameObject.Find ("WayPoint39").transform;
				wayPointList[4] = GameObject.Find ("WayPoint41").transform;
				wayPointList[5] = GameObject.Find ("PolicePoint2").transform;
				break;
				
			case 17:
				wayPointList = new Transform[6];
				wayPointList[0] = GameObject.Find ("WayPoint33").transform;
				wayPointList[1] = GameObject.Find ("WayPoint37").transform;
				wayPointList[2] = GameObject.Find ("WayPoint38").transform;
				wayPointList[3] = GameObject.Find ("WayPoint39").transform;
				wayPointList[4] = GameObject.Find ("WayPoint40").transform;
				wayPointList[5] = GameObject.Find ("StorePoint2").transform;
				break;
				
			case 18:
				wayPointList = new Transform[5];
				wayPointList[0] = GameObject.Find ("WayPoint33").transform;
				wayPointList[1] = GameObject.Find ("WayPoint37").transform;
				wayPointList[2] = GameObject.Find ("WayPoint38").transform;
				wayPointList[3] = GameObject.Find ("WayPoint43").transform;
				wayPointList[4] = GameObject.Find ("PetrolPoint").transform;
				break;
				
			case 19:
				wayPointList = new Transform[5];
				wayPointList[0] = GameObject.Find ("WayPoint33").transform;
				wayPointList[1] = GameObject.Find ("WayPoint37").transform;
				wayPointList[2] = GameObject.Find ("WayPoint38").transform;
				wayPointList[3] = GameObject.Find ("WayPoint44").transform;	
				wayPointList[4] = GameObject.Find ("SchoolPoint").transform;
				break;
				
			case 20:
				wayPointList = new Transform[3];
				wayPointList[0] = GameObject.Find ("WayPoint33").transform;
				wayPointList[1] = GameObject.Find ("WayPoint37").transform;
				wayPointList[2] = GameObject.Find ("HospitalPoint2").transform;
				break;
		}
	}

    public void loadSettings(int r,int cWP,float x,float y,float z,string col,string ty,string sis,float spe, int pi, int cInt){
        route = r;
        setWavePoints(route);
        currentWayPoint = cWP;
        targetWayPoint.position = new Vector3(x,y,z);
        colorString = col;
        carTypeString = ty;
        sizeString = sis;
        carColor = cInt;
        gameObject.GetComponent<Renderer>().material.color = gameMgr.colorArray[carColor];
        speed = spe;
        carPID = pi;
    }

}

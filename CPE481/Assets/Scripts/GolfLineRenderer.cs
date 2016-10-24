using UnityEngine;
using System.Collections;
using System;
public class GolfLineRenderer : MonoBehaviour {
	// This will be the object declaration of the line renderer itself
	private LineRenderer golfLine;
	
	// This will be the first point of the line renderer
	public Transform origin;
	
	// This will be the point to what the line renderer will connect to
	public Transform destination;
	
	// This will be the golf object in which the line will be casted from it to the destination transform vector
	public GolfBall golfObject;
	
	
	
	// Ray casting variables
	// This will check if the ray cast hit the terrain variable
	public 	string tagCheck ;
	
	
	// The distance of the ray cast
	private float rayCastDistance;
	
	// Use this for initialization
	void Start () {
		// Variables
		
		// Setting up variables for the liner enderer
		// Get the line renderer object itself
		golfLine = GetComponent<LineRenderer>();
		
		// Find the golf ball object
		golfObject = GameObject.Find("GolfBall").GetComponent<GolfBall>();
		
		
		// Set how deep the line renderer line should look
		golfLine.SetWidth(0.05f, 0.25f);
		
		// Set the origin of the line renderer
		origin = golfObject.transform;
		
		// Ray Cast variable setup
		// Set how long the ray cast line should be extended to
		rayCastDistance = 100f;
		tagCheck = "GolfCourseP1";
	}
	
	// Update is called once per frame
	void Update () {
		//Debug.DrawRay(origin.forward, origin.forward.normalized);
		/*
		bool foundHit = false;
		RaycastHit hit; // Saves information concerning raycasting
		Vector3 vect = new Vector3(0,-1,0);
		if(Physics.Raycast(origin.position, vect))
		   {
			print("NO");
			print(vect );

		}

		else
		{
			print(origin.forward);
		}
		origin = golfObject.transform;

		*/
		
		float xChange = (golfObject.speed/600f) *( Mathf.Sin(golfObject.transform.eulerAngles.x) * Mathf.Cos(golfObject.transform.eulerAngles.y));
		float yChange = (golfObject.speed/600f)*( Mathf.Sin(golfObject.transform.eulerAngles.x) * Mathf.Sin(golfObject.transform.eulerAngles.y));
		float zChange = (golfObject.speed/600f) * (Mathf.Cos(golfObject.transform.eulerAngles.x));
		//float x = origin.position.x
		
		
		float x = origin.position.x + xChange ;
		float y = origin.position.y + yChange;
		float z = origin.position.z + zChange;
		
		Vector3 finalPos = new Vector3(x, y, z);
		
		golfLine.SetPosition(0,origin.position);
		golfLine.SetPosition(1, finalPos);
		//	Debug.DrawLine(origin.position, finalPos, Color.green);
		
	}
}

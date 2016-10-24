/*This script is to check if the ball went inside the hole in the mesh
 * 
 * 
 * 
 * */

using UnityEngine;
using System.Collections;

public class ballIn : MonoBehaviour {
	// This will be for raycasting down to the hole
	//public GameObject hole;


	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
		RaycastHit hit;



		Debug.DrawLine(new Vector3(transform.position.x,transform. position.y + 10,transform.position.z), new Vector3(transform.position.x,transform. position.y,transform.position.z)
		, Color.red);
	





		if(Physics.Raycast(new Vector3(transform.position.x,transform. position.y + 10,transform.position.z), Vector3.down
		                   , out hit, 40)){
			if(hit.collider.tag == "ActualGolfHole")
			{

				print("F");
			}

			if(hit.collider.tag == "GolfBall")
			{
				print("LEVEL NOT LOAD");

				Application.LoadLevel("MainMenu");
			}
		}

	}
}

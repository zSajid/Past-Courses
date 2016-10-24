using UnityEngine;
using System.Collections;

public class CameraControl : MonoBehaviour {
	float speed = 1.5f;
	float rotationSpeed = 50;
	Vector3 startPos = new Vector3(0f,0f,0f);
	Quaternion startRot;

	GameObject building;
	// Use this for initialization
	void Start () {
		startPos = this.transform.position;
		startRot = this.transform.rotation;
	}
	
	// Update is called once per frame
	void Update () {


		// 'W' key moves camera forward
		if (Input.GetKey (KeyCode.R)) {
			this.transform.Translate(0, 0, speed);
		}

		// 'S' key moves camera back
		if (Input.GetKey (KeyCode.F)) {
			this.transform.Translate(0, 0, -speed);
		}

		// 'D' key moves camera right
		if (Input.GetKey (KeyCode.W)) {
			this.transform.Translate(0, speed, 0);
		}
		
		// 'A' key moves camera left
		if (Input.GetKey (KeyCode.S)) {
			this.transform.Translate(0, -speed ,0);
		}
		// 'D' key moves camera right
		if (Input.GetKey (KeyCode.D)) {
			this.transform.Translate(speed, 0, 0);
		}

		// 'A' key moves camera left
		if (Input.GetKey (KeyCode.A)) {
			this.transform.Translate(-speed, 0, 0);
		}

		// 'E' controls the pitch clockwise
		if (Input.GetKey (KeyCode.L)) {
			this.transform.Rotate(0, speed, 0);
		}

		// 'R' controls the pitch counter clockwise
		if (Input.GetKey (KeyCode.J)) {
			this.transform.Rotate(0, -speed, 0);
		}

		// 'Q' controls the roll clockwise
		if (Input.GetKey (KeyCode.K)) {
			this.transform.Rotate( speed, 0, 0);
			
		}

		// 'Z' controls the roll counter clockwise
		if (Input.GetKey (KeyCode.I)) {
			this.transform.Rotate( -speed, 0,0);
		}

		// 'X' controls the yaw clockwise
		if (Input.GetKey (KeyCode.Y)) {
			this.transform.Rotate( 0, 0, speed);
			
		}

		//'C' controls the yaw counter clockwise
		if (Input.GetKey (KeyCode.H)) {
			this.transform.Rotate(  0, 0, -speed);
		}

		//space bar reset position
		if (Input.GetKey (KeyCode.Space)) {
			this.transform.position = startPos;
			this.transform.rotation = startRot;
		}

	}
}

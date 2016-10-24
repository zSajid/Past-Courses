using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class GolfBall : MonoBehaviour {
	public float speed = 0f;
	public Slider sliderObject;
	public SliderForce sliderClass;
	
	float moveHorizontal;
	float moveVertical;
	public Rigidbody rb; // This will be the rigidbody for the GolfBall
	
	// This bool will detect if the ball is currently rolling
	public bool ballRolling;
	

	
	// Use this for initialization
	void Start (){
		// Instantiate a variable that will take the rigidbodies object
		rb = GetComponent<Rigidbody>();
		
		
		// This will get the force of the object and transfer it to speed
		sliderObject = GameObject.Find("Slider").GetComponent<Slider>();
		
		
		// Variables
		sliderClass = GameObject.Find("Slider").GetComponent<SliderForce>();
		ballRolling = false;
		
		// Reset the velocity
		rb.velocity = Vector3.zero;
		rb.angularVelocity = Vector3.zero;
		// "Pause" the physics
		rb.isKinematic = true;

		// Re-enable the physics
		rb.isKinematic = false;
		rb.WakeUp();
	}
	
	// Update is called once per frame
	void Update () {
		speed = 0;
		if(ballRolling == false)
		{

			// Get speed from Slider
			speed = sliderObject.value;



			
			
			
			// Check to see if user Input is good to go.
			if(sliderClass.userInput == true)
			{
				
				
				float xChange = speed *( Mathf.Sin(transform.eulerAngles.x) * Mathf.Cos(transform.eulerAngles.y));
				float yChange = speed *( Mathf.Sin(transform.eulerAngles.x) * Mathf.Sin(transform.eulerAngles.y));
				float zChange = speed * (Mathf.Cos(transform.eulerAngles.x));
				
				float x = transform.position.x + xChange ;
				float y = transform.position.y + yChange;
				float z = transform.position.z + zChange;
				
				Vector3 finalPos = new Vector3(x, y, z);
				rb.AddForce(finalPos);
				
				ballRolling = true;
				sliderClass.userInput = false;

			}
		}
		
		else
		{
			
			if((rb.velocity.z < 0.3  && rb.velocity.z > -0.3) && (rb.velocity.y < 0.3 && rb.velocity.y > -0.3)
			   &&(rb.velocity.x < 0.3 && rb.velocity.x > -0.3))
			{
				/*
				rb.angularVelocity = Vector3.zero;
				transform.eulerAngles = Vector3.zero;


				print(transform.eulerAngles);
				ballRolling = false;
				transform.eulerAngles = Vector3.zero;
				transform.rotation = Quaternion.identity;
				*/
				// Reset the velocity
				rb.velocity = Vector3.zero;
				rb.angularVelocity = Vector3.zero;
				// "Pause" the physics
				rb.isKinematic = true;
				// Do positioning, etc
				transform.rotation = Quaternion.identity;
				// Re-enable the physics
				rb.isKinematic = false;
				rb.WakeUp();
				ballRolling = false;
			}
		}
	
	}
	
	void FixedUpdate()
	{	
		
		RaycastHit hit;
		
		if (Input.GetMouseButton(0))
		{
			if (Physics.Raycast (Camera.main.ScreenPointToRay(Input.mousePosition), out hit))
			{
				float x = -Input.GetAxis("Mouse X");
				float y = -Input.GetAxis("Mouse Y");
				float speed = 0.2f;
				transform.rotation *= Quaternion.AngleAxis(x*speed, Vector3.up);
				transform.rotation *= Quaternion.AngleAxis(y*speed, Vector3.right);
			}
		}
		
		// Check to see if the player wants to move left or right prior to hitting the go button
		if(Input.GetKey(KeyCode.S)){
			transform.Rotate(Vector3.right * 0.02f);

		}
		
		if(Input.GetKey(KeyCode.W)){
			transform.Rotate(Vector3.up * 0.02f);
		}

	}
}

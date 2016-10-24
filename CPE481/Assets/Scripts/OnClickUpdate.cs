using UnityEngine;
using System.Collections;

public class OnClickUpdate : MonoBehaviour {
	public GolfBall golfObject;
	public bool clicked;

	// Use this for initialization
	void Start () {
		golfObject = GameObject.Find("GolfBall").GetComponent<GolfBall>();
		clicked =false;
	}
	
	// Update is called once per frame
	void Update () {


	}

	
	public void GoButtonOnMouseDown(){

		if(golfObject.ballRolling == false && GameObject.Find("Slider").GetComponent<SliderForce>().userInput == false )
		{
			clicked = true;
			GameObject.Find("Slider").GetComponent<SliderForce>().userInput = true;
		}

	}

	public void LeftButtonOnMouseDown(){
		golfObject.transform.Rotate(Vector3.left * 0.02f);

		print("F");

	}

	public void RightButtonOnMouseDown(){
		golfObject.transform.Rotate(Vector3.left * -0.02f);


	}
}


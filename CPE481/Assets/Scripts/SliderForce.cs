using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class SliderForce : MonoBehaviour {
	public Slider forceBar; // This is the object for which it is connected to
	public bool userInput; // This is a variable state that will turn to true if the intial value has been gotten from the user, and false if it has not
	public bool goAgain; // This is a variable to check if the user can go again and if the button is visible
	// Use this for initialization
	void Start () 
	{
		// This will initialize the bar to 0
		forceBar.value = 0;

		// This will set the max value for slider to x
		forceBar.maxValue = 6000f;
		forceBar.minValue = 0f;

		//Set stopped to false
		userInput = false;

		// Set bool goAgain to false
		goAgain = true;
	}
	
	// Update is called once per frame
	void Update () 
	{

	}


}

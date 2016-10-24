using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class UpdateStrokes : MonoBehaviour {
	private UnityEngine.UI.Text score;
	private int stroke;
	private OnClickUpdate GoButtonScript;
	// Use this for initialization
	void Start () {
		stroke = 0;
		GoButtonScript = GameObject.Find("Main Camera").GetComponent<OnClickUpdate>();
		score = GetComponent<UnityEngine.UI.Text>();
		score.text = "Strokes: " + stroke;
	}
	
	// Update is called once per frame
	void Update () {
	
		if(GoButtonScript.clicked == true)
		{
			stroke += 1;
			GoButtonScript.clicked = false;
		}

		score.text = "Strokes: " + stroke;

	}
}

using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class UpdateHole : MonoBehaviour {
	private UnityEngine.UI.Text score;
	private int Hole;

	// Use this for initialization
	void Start () {
		score = GetComponent<UnityEngine.UI.Text>();
		score.text = "Hole: 0";
	}
	
	// Update is called once per frame
	void Update () {

	}
}

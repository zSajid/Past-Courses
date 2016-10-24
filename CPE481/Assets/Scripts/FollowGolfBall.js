#pragma strict

var GolfBall : Transform;
function Start () {
	
}
 
function Update () {

transform.position = Vector3(GolfBall.transform.position.x, GolfBall.position.y + 4,GolfBall.position.z);
//Vector3(GolfBall .transform.position.x - 7, GolfBall .transform.position.y +3, GolfBall .transform.position.z - 7);
transform.LookAt(GolfBall);
}
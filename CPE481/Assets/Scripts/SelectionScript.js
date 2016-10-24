#pragma strict

function startGameLevel(sceneName : int)
	{
	 Application.LoadLevel("Hole" + sceneName);
	
	}

function returnToMain()
	{
	 Application.LoadLevel("MainMenu");
	}
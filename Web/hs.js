var partida = JSON.parse(highscores);

var tabla   = document.createElement('table');
var tblBody = document.createElement('tbody');

	var fila = document.createElement("tr");
  	var columna = document.createElement("th");
	columna.appendChild(document.createTextNode("NAME"));
	fila.appendChild(columna);
	
	columna = document.createElement("th");
	columna.appendChild(document.createTextNode("PTS"));
	fila.appendChild(columna);
	tblBody.appendChild(fila);

	
	for (var i = 0; i < 5; i++) {
 	  fila = document.createElement("tr");
	  columna = document.createElement("td");
	  columna.appendChild(document.createTextNode(partida[i].name));
	  fila.appendChild(columna);
      columna = document.createElement("td");
	    columna.appendChild(document.createTextNode(partida[i].pontos));
	    fila.appendChild(columna);
	 tblBody.appendChild(fila);   
	  }
	 
	 
	
	 
	tabla.appendChild(tblBody);
	var body = document.getElementById("div1")
	body.appendChild(tabla);
	tabla.setAttribute("border-spacing", "0");
	tabla.setAttribute("border-collapse", "collapse");

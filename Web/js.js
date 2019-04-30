var partida = JSON.parse(data);
var aux = JSON.parse(partidaValues);

var tabla   = document.createElement('table');
	var tblBody = document.createElement('tbody');

	var fila = document.createElement("tr");
  	var columna = document.createElement("th");
	columna.appendChild(document.createTextNode("NAME"));
	fila.appendChild(columna);
	columna = document.createElement("th");
	columna.appendChild(document.createTextNode("HEIGHT"));
	fila.appendChild(columna);

	for(var i = 1; i <= aux.nr;i++){
		columna = document.createElement("th");
	    columna.appendChild(document.createTextNode("RONDA N"+i));
	    fila.appendChild(columna);
	    columna = document.createElement("th");
	    columna.appendChild(document.createTextNode("TRY"));
	    fila.appendChild(columna);
	}

	columna = document.createElement("th");
	columna.appendChild(document.createTextNode("PTS"));
	fila.appendChild(columna);
	columna = document.createElement("th");
	columna.appendChild(document.createTextNode("PTS%"));
	fila.appendChild(columna);
	tblBody.appendChild(fila);

	
	for (var i = 0; i < aux.nj; i++) {
 		var pts =0;
 	  var t = 0;
 	  var c = 0;
	  fila = document.createElement("tr");
	  columna = document.createElement("td");
	  columna.appendChild(document.createTextNode(partida[i].name));
	  fila.appendChild(columna);
	  columna = document.createElement("td");
	  columna.appendChild(document.createTextNode(partida[i].height));
	  fila.appendChild(columna);
	  for (var j = 0; j < aux.nr; j++) {

	    columna = document.createElement("td");
	    columna.appendChild(document.createTextNode(partida[i].rondas[j].pontos));
	    fila.appendChild(columna);
	    pts+=partida[i].rondas[j].pontos;
	    var intentos = document.createElement("td");
	    intentos.appendChild(document.createTextNode(partida[i].rondas[j].tentativas));
	    fila.appendChild(intentos);
	    t+=partida[i].rondas[j].tentativas;
	    c+=partida[i].rondas[j].cestos;
	  }
	 
	  var pontos = document.createElement("td");
	    pontos.appendChild(document.createTextNode(pts));
	    fila.appendChild(pontos);
	var per = document.createElement("td");
	var porcentaje = Number(((c/t)*100).toFixed(1));
	    per.appendChild(document.createTextNode(porcentaje));
	    fila.appendChild(per);

	  tblBody.appendChild(fila);
	}
	 
	tabla.appendChild(tblBody);
	var body = document.getElementById("div1")
	body.appendChild(tabla);
	tabla.setAttribute("border-spacing", "0");
	tabla.setAttribute("border-collapse", "collapse");

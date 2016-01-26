var studies_types = [];



function on_studies_change() {
	$('#schedule_div').hide('Drop');
	$('#year_div').hide();
	$('#semester_div').hide('Drop');
	$('#date_from_div').hide('Drop');
	$('#date_to_div').hide('Drop');
	$('#submit_div').hide('Drop');
	
	var selected = $('#studies_select').val();
	if(selected == -1) {
		$('#study_year_div').hide('Drop');
		return;
	};

	$('#study_year_select').find('option').remove();
	
	$('#study_year_select').append($('<option>', {value:-1, text:'[ WYBIERZ ROK STUDIÓW ]'}));
	$.each(studies_types[selected].years, function(index, element) {
		$('#study_year_select').append($('<option>', {value:element, text:element}));
	});
	
	$('#study_year_div').show('Drop');	
};




function on_year_of_studies_change() {
	$('#schedule_div').hide('Drop');
	$('#semester_div').hide('Drop');
	$('#date_from_div').hide('Drop');
	$('#date_to_div').hide('Drop');
	$('#submit_div').hide('Drop');
	
	var selected = $('#study_year_select').val();
	if(selected == -1) {
		$('#year_div').hide('Drop');
		return;
	};
	
	var studies_selected = $('#studies_select').val();
	
	$('#year_select').find('option').remove();
	$('#year_select').append($('<option>', {value:-1, text:'[ WYBIERZ ROK AKADEMICKI ]'}));
	
	$.each(studies_types[studies_selected].available_years, function(index, element) {
		var t = String(element).concat('/').concat(String(parseInt(element) + 1));
		$('#year_select').append($('<option>', {value:element, text:t}));
	});
			
	$('#year_div').show('Drop');	
};




function on_year_change() {
	$('#schedule_div').hide('Drop');
	$('#date_from_div').hide('Drop');
	$('#date_to_div').hide('Drop');
	$('#submit_div').hide('Drop');
	
	var selected = $('#year_select').val();
	if(selected == -1) {
		$('#semester_div').hide('Drop');
		return;
	};

	$('#semester_div').show('Drop');	
};




function on_semester_change() {
	$('#schedule_div').hide('Drop');

	var selected = $('#semester_select').val();
	
	if(selected == -1) {
		$('#date_from_div').hide('Drop');
		$('#date_to_div').hide('Drop');
		$('#submit_div').hide('Drop');
		return;
	};

	if($('#date_from_input').val().length == 0) {
		var date = new Date();
		
		var year = date.getFullYear();
		var month = (date.getMonth() + 1 < 10 ? '0' : '') + (date.getMonth() + 1);
		var day = (date.getDate() < 10 ? '0' : '') + date.getDate();
		
		$('#date_from_input').val(day + '-' + month + '-' + year);
	};
	$('#date_from_div').show('Drop');
	$('#date_to_div').show('Drop');
	$('#submit_div').show('Drop');
};




function render_plan(text) {
	var plan = JSON.parse(text);
	
	$('#config_div').hide('Drop');
	$('#expand_config_div').show('Drop');
	
	var accordion = $('#schedule_div');
	accordion.show('Drop');
	
	accordion.empty();
	
	for(var i = 0; i < plan.schedule.length; i++) {
		var date = plan.schedule[i].date;
		
		accordion.append('<h3>' + date + '</h3>');
		accordion.append('<div id="' + date + '"></div>');
		
		$('#' + date).append('<table id="table-' + date + '" class="tablesorter"></table>');
		$('#table-' + date).append('<thead id="header-' + date + '"></thead>');
		$('#table-' + date).append('<tbody id="rows-' + date +'"></tbody>');
		$('#header-' + date).append('<tr><th>Od</th><th>Do</th><th>Sala</th><th>Przdmiot</th><th>Prowadzący</th></tr>'); 

		for(var j = 0; j < plan.schedule[i].events.length; j++) {
			var event = plan.schedule[i].events[j];
			$('#rows-' + date).append('<tr><td>' + event.begin + '</td><td>' + event.end + '</td><td>' + event.place +'</td><td>' + event.classes + '</td><td>' + event.person + '</td></tr>'); 
		};
		
		$('#table-' + date).tablesorter();    
		$('#table-' + date).trigger("update");
   	};
	
    accordion.accordion("refresh");
};




function readTextFile(file, callback) {
    var rawFile = new XMLHttpRequest();
    
    rawFile.overrideMimeType("application/json");
    rawFile.open("GET", file, true);
    rawFile.onreadystatechange = function() {
        if (rawFile.readyState === 4 && rawFile.status == "200") {
            callback(rawFile.responseText);
        }
    }
    rawFile.send(null);
};




function on_submit() {
	readTextFile("data/plan.json", render_plan);
};




function on_expand() {
	$('#config_div').show('Drop');
	$('#expand_config_div').hide('Drop');
	$('#schedule_div').hide('Drop');
};

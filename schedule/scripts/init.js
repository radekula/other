$( document ).ready(function() {
	$.getJSON( 'data/config.json', function( json ) {
		
		$('#header_title').append(json.page_title);
		
		$('#studies_select').append($('<option>', {value:-1, text:'[ WYBIERZ STUDIA ]'}));
		$.each(json.studies_types, function(index, element) {
			studies_types[element.value] = element;
			$('#studies_select').append($('<option>', {value:element.value, text:element.name}));
		});
		
		$('#study_year_select').append($('<option>', {value:-1, text:'[ WYBIERZ ROK STUDIÓW ]'}));
		$('#year_select').append($('<option>', {value:-1, text:'[ WYBIERZ ROK AKADEMICKI ]'}));

// configuring semester selector
		$('#semester_select').append($('<option>', {value:-1, text:'[ WYBIERZ SEMESTR ]'}));
		$.each(json.semester_in_year, function(index, element) {
			$('#semester_select').append($('<option>', {value:element, text:element}));
		});
		
// configuring elements
		$('#studies_select').selectmenu().on('selectmenuchange', on_studies_change);
		$('#study_year_select').selectmenu().on('selectmenuchange', on_year_of_studies_change);
		$('#year_select').selectmenu().on('selectmenuchange', on_year_change);
		$('#semester_select').selectmenu().on('selectmenuchange', on_semester_change);
		$('#date_from_input').datepicker().datepicker("option", "dateFormat", "dd-mm-yy").on('selectmenuchange', on_year_of_studies_change);
		$('#date_to_input').datepicker().datepicker("option", "dateFormat", "dd-mm-yy").on('selectmenuchange', on_year_of_studies_change);
		$('#submit_button').button().click(on_submit);
		$('#expand_button').button().click(on_expand);
		$('#schedule_div').accordion();
		
// hiding everything
		$('#study_year_div').hide();
		$('#year_div').hide();
		$('#semester_div').hide();
		$('#date_from_div').hide();
		$('#date_to_div').hide();
		$('#submit_div').hide();
		$('#schedule_div').hide();
		$('#show_config_div').hide();
		$('#expand_config_div').hide('Drop');
	});
});

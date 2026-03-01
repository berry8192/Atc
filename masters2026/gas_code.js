function doGet(e) {
  var sheet = SpreadsheetApp.getActiveSpreadsheet().getSheetByName(e.parameter.sheet || "Sheet1");

  if (e.parameter.action === "write") {
    var row = parseInt(e.parameter.row);
    var col = parseInt(e.parameter.col);
    var values = JSON.parse(e.parameter.values);
    sheet.getRange(row, col, values.length, values[0].length).setValues(values);
    return ContentService.createTextOutput(JSON.stringify({status: "ok"})).setMimeType(ContentService.MimeType.JSON);
  }

  var range = e.parameter.range || "A1:Z100";
  var data = sheet.getRange(range).getValues();
  return ContentService.createTextOutput(JSON.stringify(data)).setMimeType(ContentService.MimeType.JSON);
}

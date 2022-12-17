module subway {
	requires javafx.controls;
	requires javafx.fxml;
	requires javafx.base;
	requires org.jsoup;
	requires java.desktop;
	requires javafx.graphics;
	requires java.sql;
	requires json.simple;
	
	opens application to javafx.graphics, javafx.fxml;
}

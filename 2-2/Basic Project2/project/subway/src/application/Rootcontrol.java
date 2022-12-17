package application;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.Map;
import java.io.IOException;
import java.net.URL;
import java.util.ResourceBundle;

import org.json.simple.parser.ParseException;

import javafx.fxml.Initializable;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.image.ImageView;
import javafx.scene.layout.AnchorPane;
import javafx.scene.paint.Paint;
import javafx.scene.shape.Circle;
import javafx.scene.shape.Rectangle;
import javafx.scene.text.Font;

public class Rootcontrol implements Initializable {

	@FXML
	private TextField Start_station;
	@FXML
	private TextField End_station;
	@FXML
	private ScrollPane scrollPane;
	@FXML
	private ImageView imageView;
	@FXML
	private AnchorPane Main_P;
	@FXML
	private Scene scene;

	private ListView<String> list;

	private ArrayList<Rectangle> re_list = new ArrayList<Rectangle>();
	private ArrayList<Label> label_list = new ArrayList<Label>();
	private ArrayList<Circle> circle_list = new ArrayList<Circle>();
	private ArrayList<Label> co_list = new ArrayList<Label>();
	private ArrayList<String> line_list = new ArrayList<String>();

	private double zoom = 1.0;
	private Station start = null;
	private Station end = null;
	private String input = "";

	static boolean check = false;
	static boolean s_check = false;
	static boolean e_check = false;
	static HashMap<String, Station> sel_st;
	static Label im = new Label();

	class chage extends Thread {
		public void run() {
			while (true) {

				double height = Main_P.getHeight() - 200.0;
				double width = Main_P.getWidth() - 335.0;
				if (width * (double) (325.0 / 400.0) < height) {
					height = width * (double) (325.0 / 400.0);
				} else {
					width = height * (double) (400.0 / 325.0);
				}
				scrollPane.setPrefWidth(width);
				scrollPane.setPrefHeight(height);
				if (400.0 > width) {
					width = 400.0;
				}
				if (320.0 > height) {
					height = 320.0;
				}
				imageView.setFitWidth(width * zoom);
				imageView.setFitHeight((height - 5.0) * zoom);
			}
		}
	}

	@Override
	public void initialize(URL arg0, ResourceBundle arg1) {

		Main_P.getChildren().add(im);
		chage chage = new chage();
		chage.start();

		Main_P.setPrefHeight(622.0);
		Main_P.setPrefWidth(867.0);

		Main_P.getStylesheets().add(getClass().getResource("application.css").toString());

		// 사진 줌인
		scrollPane.setOnScroll(event -> {
			double Width = imageView.getFitWidth();
			double Height = imageView.getFitHeight();
			if (event.getDeltaY() > 0) {
				zoom *= 1.1;
				if (zoom > 2500.0 / 400.0)
					zoom = 2500.0 / 400.0;
			} else if (event.getDeltaY() < 0) {
				zoom /= 1.1;
				if (zoom < 1.0)
					zoom = 1.0;
			}

			imageView.setFitWidth(Width * zoom);
			imageView.setFitHeight(Height * zoom);
		});
	}

	// 시작역 입력
	public void Input_start(ActionEvent event) {
		s_check = false;
		input = Start_station.getText();
		check = true;
		sel(input);
	}

	// 도착역 입력
	public void Input_end(ActionEvent event) {

		e_check = false;
		input = End_station.getText();
		check = false;
		sel(input);

	}

	// 출발,도착역 선택
	public void sel(String input) {

		Main_P.getChildren().remove(list);
		sel_st = new HashMap<String, Station>();
		list = new ListView<String>();

		list.setPrefWidth(269.0);
		list.setOnMouseClicked(event -> {
			Object obj = list.getSelectionModel().getSelectedItem();

			if (check) {
				start = sel_st.get(obj.toString());
				s_check = true;
				Start_station.setText(obj.toString());
			} else {
				end = sel_st.get(obj.toString());
				e_check = true;
				End_station.setText(obj.toString());
			}
			while (list.getItems().size() > 0) {
				list.getItems().remove(0);
			}
			try {
				sol();
			} catch (IOException | ParseException e) {
				e.printStackTrace();
			}
			Main_P.getChildren().remove(list);
		});
		
		//입력된 문자가 포함되어 있는 문자들을 담을 리스트
		ArrayList<String> tmp_list = new ArrayList<String>();
		//리스트뷰 초기화
		while (list.getItems().size() > 0) {
			list.getItems().remove(0);
		}
		
		//역 정보들을 모두 비교하여 입력된 문자가 포함되었는지 확인
		for (Map.Entry<String, ArrayList<Station>> pair : Main.St.entrySet()) {
			ArrayList<Station> tmp = pair.getValue();
			for (int i = 0; i < tmp.size(); i++) {
				Station cur = tmp.get(i);
				//문자가 포함되었다면 리스트에 담기
				if (cur.Station_name.contains(input) && !tmp_list.contains(cur.Station_name)) {
					tmp_list.add(cur.Station_name);
					sel_st.put(cur.Station_name, cur);
				}
			}
		}
		//정렬 후 리스트뷰에 담고 ui구현
		Collections.sort(tmp_list);
		for (String copy : tmp_list) {
			list.getItems().add(copy);
		}
		double list_height = list.getItems().size() * 20.0;
		if (list_height > 150.0)
			list_height = 150.0;
		list.setPrefHeight(list_height);
		double Top = 0.0;
		if (check)
			Top = 170.0;
		else
			Top = 270.0;
		AnchorPane.setTopAnchor(list, Top);
		AnchorPane.setRightAnchor(list, 43.0);
		Main_P.getChildren().add(list);
	}

	// 최단거리 출력
	public void sol() throws IOException, ParseException {

		if (s_check && e_check) {

			for (int i = 0; i < circle_list.size(); i++) {
				Main_P.getChildren().remove(circle_list.get(i));
				Main_P.getChildren().remove(co_list.get(i));
			}

			for (int i = 0; i < re_list.size(); i++) {
				Main_P.getChildren().remove(re_list.get(i));
			}

			for (int i = 0; i < label_list.size(); i++) {
				Main_P.getChildren().remove(label_list.get(i));
			}

			line_list = new ArrayList<String>();
			circle_list = new ArrayList<Circle>();
			co_list = new ArrayList<Label>();
			label_list = new ArrayList<Label>();
			re_list = new ArrayList<Rectangle>();
			n_s sol = Main.dijkstra(start, end);

			set_rect(500.0, sol.line, 30.0);

			String t = Integer.toString(sol.time % 60) + "분";
			if (sol.time >= 60) {
				t = Integer.toString(sol.time / 60) + "시간 " + t;
			}

			set_label(t, 20.0, 100.0, 30.0);

			set_label(start.Station_name, 13.0, 60.0, 10.0);

			set_label(end.Station_name, 13.0, 60.0, 510.0);

			double left = 0.0;
			double pre = 0.0;
			int pre_time = 0;

			for (int i = 0; i < sol.transfer.size(); i++) {
				var tmp = sol.transfer.get(i);
				double width = 500.0 * ((double) tmp.time / (double) sol.time) - pre;

				set_rect(width, tmp.line, 30.0 + left);
				set_label(tmp.Station_name, 13.0, 60.0, 10.0 + width + left);
				set_label(Integer.toString((tmp.time - pre_time)) + "분", 16.0, 32.0, 15.0 + width / 2.0 + left);

				pre_time = tmp.time;
				left += width;
				pre = 500.0 * ((double) tmp.time / (double) sol.time);
			}

			set_label(Integer.toString((sol.time - pre_time)) + "분", 16.0, 32.0, 15.0 + (500 - pre) / 2.0 + left);

			for (int i = 0; i < re_list.size(); i++) {
				if (i < 2) {
					re_list.get(i).setArcHeight(10.0);
					re_list.get(i).setArcWidth(10.0);
					if (i == 1) {
						re_list.get(i).setWidth(re_list.get(i).getWidth() + 10.0);
					}
				}
				Main_P.getChildren().add(re_list.get(i));
			}
			
			for (int i = 0; i < label_list.size(); i++) {
				Main_P.getChildren().add(label_list.get(i));
			}
			
			for (int i = 0; i < line_list.size(); i++) {

				set_cir(i);

			}
			try {
				Main_P.getChildren().remove(im);
				String tmp = start.Station_name;
				tmp = tmp.replace("역", "");
				im = new Label(api_test.test(tmp));
				im.setFont(new Font(20.0));
				AnchorPane.setBottomAnchor(im, 30.0);
				AnchorPane.setRightAnchor(im, 50.0);
				Main_P.getChildren().add(im);
			} catch (IOException | ParseException e) {
				e.printStackTrace();
			}
		}
	}

	// 라벨 생성
	public void set_label(String la_name, double font, double bot, double left) {
		Label la = new Label(la_name);
		label_list.add(la);
		la.setFont(new Font(font));
		AnchorPane.setBottomAnchor(la, bot);
		AnchorPane.setLeftAnchor(la, left);
	}

	// 사각형 생성
	public void set_rect(double width, String line, double left) {
		Rectangle re = new Rectangle();
		re.setStyle("-fx-stroke: black;");
		re_list.add(re);
		re.setHeight(25.0);
		re.setWidth(width);
		Paint paint = set_co(line);
		if (!line_list.contains(line)) {
			line_list.add(line);
		}
		re.setFill(paint);
		AnchorPane.setBottomAnchor(re, 30.0);
		AnchorPane.setLeftAnchor(re, left);
	}

	//색별로 호선을 알려줄 원 생성
	public void set_cir(int i) {
		Circle cir = new Circle(10.0);
		cir.setFill(set_co(line_list.get(i)));
		Label co_la = new Label(line_list.get(i));
		if (i == 0) {
			i = line_list.size();
		}
		co_la.setFont(new Font(13.0));
		AnchorPane.setBottomAnchor(cir, 50.0 + (double) (line_list.size() - i + 1) * 30.0);
		AnchorPane.setRightAnchor(cir, 150.0);
		AnchorPane.setBottomAnchor(co_la, 50.0 + (double) (line_list.size() - i + 1) * 30.0);
		AnchorPane.setRightAnchor(co_la, 50.0);
		Main_P.getChildren().add(cir);
		Main_P.getChildren().add(co_la);

		co_list.add(co_la);
		circle_list.add(cir);
	}

	// 호선별 색 반환
	public Paint set_co(String Line) {
		String color = "#0D347F";
		if (Line == "1호선")
			color = "#0D347F";

		else if (Line.equals("2호선"))
			color = "#3B9F37";

		else if (Line.equals("3호선"))
			color = "#3B9F37";

		else if (Line.equals("4호선"))
			color = "#3165A8";

		else if (Line.equals("5호선"))
			color = "#703E8C";

		else if (Line.equals("6호선"))
			color = "#904D23";

		else if (Line.equals("7호선"))
			color = "#5B692E";

		else if (Line.equals("8호선"))
			color = "#C82363";

		else if (Line.equals("9호선"))
			color = "#B39627";

		else if (Line.equals("분당선"))
			color = "#DBA829";

		else if (Line.equals("신분당선"))
			color = "#971F2D";

		else if (Line.equals("경의중앙선"))
			color = "#76B69B";

		else if (Line.equals("경춘선"))
			color = "#2D9B76";

		else if (Line.equals("공항철도"))
			color = "#6CA8CE";

		else if (Line.equals("의정부경전철"))
			color = "#E78522";

		else if (Line.equals("수인분당선"))
			color = "#DBA829";

		else if (Line.equals("에버라인"))
			color = "#6FB26C";

		return javafx.scene.paint.Color.web(color);
	}

	// 출발역,도착역 선택

	public void del() {
		Main_P.getChildren().remove(list);

	}
}

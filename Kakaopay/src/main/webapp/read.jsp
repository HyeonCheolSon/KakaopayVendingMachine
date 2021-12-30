<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ page import="java.sql.*" %>

<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>.</title>
</head>
<body>
<%	
	//mariaDB 준비
	Class.forName("org.mariadb.jdbc.Driver");
	System.out.println("mariadb 사용가능");
	
	// mariaDB 연결
	Connection conn = DriverManager.getConnection("jdbc:mariadb://127.0.0.1:3306/mask","root","sulc5246");
	System.out.println(conn + "<-- conn");
	
	// 쿼리
	PreparedStatement stmt = conn.prepareStatement("SELECT * FROM masktable ORDER BY k_id DESC LIMIT 1");
	System.out.println(stmt + "<-- stmt");
	
	// 쿼리 실행
	ResultSet rs = stmt.executeQuery();
	
%>
<%
		while(rs.next()){
%>
<id><%=rs.getString("id") %></id>
<name><%=rs.getString("name") %></name>
<time><%=rs.getString("major") %></time>
<%
		}
%>
</body>
</html>
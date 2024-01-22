<%-- 
    Document   : index
    Created on : 6.12.2019, 10:35:36
    Author     : virius
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@page import = "java.util.*" %>
<!DOCTYPE html>
<html>
    <!--  toto je komentář -->
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Nepřesný čas</title>
    </head>
    <body>
        <h1>Je právě tolik hodin, kolik právě je. </h1>
        <p>
            Váš požadavek dorazil na server v <%= new Date() %>
        </p>
        
        <%
            if((new Date().getHours() <= 12)) {
        %>
        Je dopoledne.
        <% }else{ %>
        Je odpoledne.
        <%}%>
        
    </body>
</html>

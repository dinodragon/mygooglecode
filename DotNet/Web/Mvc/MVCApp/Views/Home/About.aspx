<%@ Page Language="C#" MasterPageFile="~/Views/Shared/Site.Master" AutoEventWireup="true" CodeBehind="About.aspx.cs" Inherits="MVCApp.Views.Home.About" %>

<asp:Content ID="aboutContent" ContentPlaceHolderID="MainContent" runat="server">
    <h2>About Us</h2>
    <p>
        <em><%= Html.Encode(ViewData["Message"])%></em>
    </p>
</asp:Content>

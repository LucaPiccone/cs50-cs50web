from django import forms 

class CreateWiki(forms.Form):
    title = forms.CharField(label="Title")
    content = forms.CharField(widget=forms.Textarea, label="Content")

class UpdateWiki(forms.Form):
    title = forms.CharField(widget=forms.HiddenInput())
    content = forms.CharField(widget=forms.Textarea(attrs=None))
from django import forms

from .models import Listing, Categorie

# https://chat.openai.com

class CreateLising(forms.ModelForm):
    class Meta:
        model = Listing
        exclude = ['user_id', 'auction_ended', 'winner']
        fields = '__all__'

        category_id = forms.ModelMultipleChoiceField(
            queryset=Categorie.objects.all()
        )
        
        widgets = {
            'title': forms.TextInput(attrs={'class': 'form-control'}),
            'description': forms.Textarea(attrs={'class': 'form-control'}),
            'category_id': forms.SelectMultiple(attrs={'class': 'form-control form-row'}),
            'brand_id': forms.Select(attrs={'class': 'form-control col-md-4'}),
            'image': forms.URLInput(attrs={'class': 'form-control', 'placeholder': 'URL to Image'}),
            # 'buy_now_price': forms.NumberInput(attrs={'class': 'form-control price_input', 'placeholder': 'Buy now price'}),
            'starting_bid_price': forms.NumberInput(attrs={'class': 'form-control', 'placeholder': '$ (CAD)'}),
            # 'end_time': forms.DateTimeInput(attrs={'class': 'form-control', 'type': 'datetime-local'}),
        }

        labels = {
            'category_id': "Category",
            'brand_id': "Brand"
        }

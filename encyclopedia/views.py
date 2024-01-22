from django.contrib import messages
from django.http import HttpResponseNotFound, Http404, JsonResponse
from django.shortcuts import HttpResponse, redirect, render
from django.template.loader import render_to_string
from markdown2 import Markdown
import random

from . import util, forms


def index(request):
    return render(request, "encyclopedia/index.html", {
        "entries": util.list_entries()
    })


def wiki(request, name):
    entry = util.get_entry(name)
    
    if entry:
        # https://github.com/trentm/python-markdown2
        entry = Markdown().convert(entry)
        return render(request, 'encyclopedia/wiki.html', {
            "entry": entry,
            "title": name
        })
    else:
        # https://docs.djangoproject.com/en/5.0/topics/http/views/#customizing-error-views
        raise Http404(f"A Wiki for {name} does not exist")
        

def search(request):
    if request.method == 'POST':
        search = request.POST
        title = search['q'].lower()

        entries = util.list_entries()
        
        lowercase_entries = []
        for entry in entries:
            lowercase_entries.append(entry.lower())

        if title in lowercase_entries:
            return redirect(f'wiki/{title}')

        else:
            search_entry = []     
            for entry in entries:
                if search['q'].lower() in entry.lower():
                    search_entry.append(entry)

            return render(request, 'encyclopedia/search.html', {
                'search_entry': search_entry
            })
    else:
        return HttpResponse('hi')

    # Responsive search bar 
    # if request.method == "GET":
    #     search = request.GET.get('data')
    #     entries = util.list_entries()
        
    #     search_entry = []

    #     # https://www.askpython.com/python/list/find-string-in-list-python
    #     for entry in entries:
    #         if search.lower() in entry.lower():
    #             search_entry.append(entry)

    #     # https://stackoverflow.com/questions/70652414/how-to-render-django-template-after-ajax-call
    #     html = render_to_string('encyclopedia/search.html', {
    #         'search_entry': search_entry
    #     })
    #     print(html)

    #     return JsonResponse({'data': html}, safe=False)
    # else:
    #     data = request.POST
    #     title = data['q']
    #     return redirect(f'wiki/{title}')
            

def create(request):
    # https://docs.djangoproject.com/en/5.0/topics/forms/
    if request.method == "GET":
        form = forms.CreateWiki()

        return render(request, "encyclopedia/create.html", {
            "form": form
        })

    else:
        form = forms.CreateWiki(request.POST)

        if form.is_valid():
            entry = form.cleaned_data
            title = entry["title"].capitalize()
            content = entry["content"]

            entries = util.list_entries()
        
            lowercase_entries = []
            for entry in entries:
                lowercase_entries.append(entry.lower())
            
            if title.lower() in lowercase_entries:
                # https://docs.djangoproject.com/en/5.0/ref/contrib/messages/
                messages.error(request, "The Wiki entry you tried to create already exists.")
                return redirect('/create')
            else:
                util.save_entry(title, content)

            return redirect(f'wiki/{title}')


def randompage(request):
    entries = util.list_entries()

    random_entry = random.choice(entries)

    return redirect(f'wiki/{random_entry}')

def update(request):
    if request.method == "GET":
        data = request.GET

        title = data['title']

        # Retreive entry given the title 
        entry = util.get_entry(title)

        form = forms.UpdateWiki()

        # https://stackoverflow.com/questions/813418/django-set-field-value-after-a-form-is-initialized
        form.fields['title'].initial = title
        form.fields['content'].initial = entry
        
        return render(request, 'encyclopedia/update.html', {
            "form": form,
            "title": title
        })

    else:
        data = request.POST
        
        content = data['content']
        title = data['title']

        util.save_entry(title, content)

        return redirect(f'wiki/{title}')
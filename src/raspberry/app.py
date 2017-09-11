import json
import urllib2
from flask import Flask, url_for, request, render_template


app = Flask(__name__, static_url_path='')

@app.route('/')
def welcome():
    return app.send_static_file('index.html')

@app.route('/gameon')
def game_on():
    return app.send_static_file('gameon.html')

@app.route("/gameover")
def get_data():
	return str(json.load(urllib2.urlopen("http://harmannenfaltned.no/api")))

@app.route('/showscore/')
def hello(score=100000):
    return render_template('showscore.html', score=score)


@app.route("/api/startgame")
def start_game():
	# TODO: serial call to arduino to start the game
    return "Starting the game."

@app.route("/api/endgame")
def get_score():
	# TODO: serial call to arduino to stop the game
	# 
    return "Score = "  

def has_no_empty_params(rule):
    defaults = rule.defaults if rule.defaults is not None else ()
    arguments = rule.arguments if rule.arguments is not None else ()
    return len(defaults) >= len(arguments)

@app.route("/api")
def site_map():
    links = []
    for rule in app.url_map.iter_rules():
        # Filter out rules we can't navigate to in a browser
        # and rules that require parameters
        if "GET" in rule.methods and has_no_empty_params(rule):
            url = url_for(rule.endpoint, **(rule.defaults or {}))
            links.append((url, rule.endpoint))
    # links is now a list of url, endpoint tuples
    return str(links)


if __name__ == "__main__":
    app.run()
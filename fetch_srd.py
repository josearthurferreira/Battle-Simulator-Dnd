import urllib.request
import json
import os

def fetch_data(url):
    req = urllib.request.Request(url, headers={'User-Agent': 'Mozilla/5.0'})
    with urllib.request.urlopen(req) as response:
        return json.loads(response.read().decode())

def process_races():
    base_url = "https://www.dnd5eapi.co"
    races_index = fetch_data(base_url + "/api/races")
    formatted_races = []

    for item in races_index['results']:
        race_data = fetch_data(base_url + item['url'])
        
        ability_bonuses = [0, 0, 0, 0, 0, 0]
        
        for bonus in race_data.get('ability_bonuses', []):
            attr_index = {
                "STR": 0, "DEX": 1, "CON": 2, "INT": 3, "WIS": 4, "CHA": 5
            }.get(bonus['ability_score']['index'].upper(), -1)
            
            if attr_index != -1:
                ability_bonuses[attr_index] = bonus['bonus']

        clean_race = {
            "id": race_data['index'],
            "name": race_data['name'],
            "speed": race_data['speed'],
            "ability_bonuses": ability_bonuses,
            "starting_proficiencies": [prof['index'] for prof in race_data.get('starting_proficiencies', [])],
            "traits": [trait['index'] for trait in race_data.get('traits', [])]
        }
        formatted_races.append(clean_race)

    with open("data/races.json", "w", encoding="utf-8") as f:
        json.dump(formatted_races, f, indent=4)

def process_backgrounds():
    base_url = "https://www.dnd5eapi.co"
    bg_index = fetch_data(base_url + "/api/backgrounds")
    formatted_bgs = []

    for item in bg_index['results']:
        bg_data = fetch_data(base_url + item['url'])
        
        clean_bg = {
            "id": bg_data['index'],
            "name": bg_data['name'],
            "starting_proficiencies": [prof['index'] for prof in bg_data.get('starting_proficiencies', [])]
        }
        formatted_bgs.append(clean_bg)

    with open("data/backgrounds.json", "w", encoding="utf-8") as f:
        json.dump(formatted_bgs, f, indent=4)

os.makedirs("data", exist_ok=True)
process_races()
process_backgrounds()
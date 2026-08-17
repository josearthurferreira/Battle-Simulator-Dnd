import urllib.request
import json
import os

def fetch_data(url):
    req = urllib.request.Request(url, headers={'User-Agent': 'Mozilla/5.0'})
    with urllib.request.urlopen(req) as response:
        return json.loads(response.read().decode())

def process_spells():
    base_url = "https://www.dnd5eapi.co"
    spells_index = fetch_data(base_url + "/api/spells")
    formatted_spells = []

    for item in spells_index['results']:
        spell_data = fetch_data(base_url + item['url'])
        
        clean_spell = {
            "id": spell_data['index'],
            "name": spell_data['name'],
            "level": spell_data['level'],
            "school": spell_data['school']['index'],
            "casting_time": spell_data.get('casting_time', ''),
            "range": spell_data.get('range', ''),
            "duration": spell_data.get('duration', ''),
            "requires_concentration": spell_data.get('concentration', False)
        }

        if 'damage' in spell_data:
            if 'damage_type' in spell_data['damage']:
                clean_spell['damage_type'] = spell_data['damage']['damage_type']['index']
            if 'damage_at_slot_level' in spell_data['damage']:
                clean_spell['damage_slots'] = spell_data['damage']['damage_at_slot_level']
            elif 'damage_at_character_level' in spell_data['damage']:
                clean_spell['damage_character_levels'] = spell_data['damage']['damage_at_character_level']

        if 'dc' in spell_data:
            clean_spell['save_type'] = spell_data['dc']['dc_type']['index']

        formatted_spells.append(clean_spell)

    with open("data/spells.json", "w", encoding="utf-8") as f:
        json.dump(formatted_spells, f, indent=4)

os.makedirs("data", exist_ok=True)
process_spells()
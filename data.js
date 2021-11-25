use GalleryTEC
db.users.remove({});
db.users.insert({"username": "cuadri", "password": "maxito", 
	"galleries": [
		{"name": "Pop Art", 
			"images": [
				{"name": "Donuts",
				"author": "Andy Warhol",
				"year": "2017",
				"size": "500x500",
				"description": "4 donuts"},
				{"name": "Foca",
				"author": "Adri C",
				"year": "2021",
				"size": "200x200",
				"description": "foquita"}
			]
		},
		{"name": "Surrealism", 
			"images": [
				{"name": "Imagen3",
				"author": "Autor3",
				"year": "3333",
				"size": "333x333",
				"description": "tres"},
				{"name": "IMagen4",
				"author": "a4",
				"year": "2044",
				"size": "2004x200",
				"description": "uwu4"}
			]
		}
	]
}); 
				

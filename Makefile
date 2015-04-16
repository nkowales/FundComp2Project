CMP = g++
MAIN = main
DOT_OS = AnimatedTexture.o Block.o Bullet.o Camera.o ContentManager.o Fireball.o Geom.o LayerController.o MapLayer.o ObjectLayer.o OneWayPlatform.o Player.o PlayerSpawn.o TestCollider.o Texture.o TileLayer.o Tileset.o TriggerArea.o WorldDebugger.o WorldMap.o WorldObject.o

HEADERS = AnimatedTexture.h Block.h Bullet.h Camera.h ContentManager.h Fireball.h Geom.h LayerController.h MapLayer.h ObjectLayer.h OneWayPlatform.h Player.h PlayerSpawn.h TestCollider.h Texture.h TileLayer.h Tileset.h TriggerArea.h WorldDebugger.h WorldMap.h WorldObject.h WorldIO.h Animation.h CollisionGroup.h GameConstants.h ObjectHeaders.h

FUNC1 = AnimatedTexture
FUNC2 = Block 
FUNC3 = Bullet
FUNC4 = Camera
FUNC5 = ContentManager
FUNC6 = Fireball
FUNC7 =  Geom
FUNC8 = LayerController
FUNC9 = MapLayer
FUNC10 = ObjectLayer
FUNC11 = OneWayPlatform
FUNC12 = Player
FUNC13 = PlayerSpawn
FUNC14 = TestCollider
FUNC15 = Texture
FUNC16 = TileLayer 
FUNC17 =  Tileset
FUNC18 = TriggerArea 
FUNC19 = WorldDebugger
FUNC20 = WorldMap
FUNC21 = WorldObject
    
EXEC = fc2proj

FLAGS = -lSDL2 -lSDL2_image -lSDL2main -std=c++11 -static-libstdc++

$(EXEC): $(MAIN).o $(DOT_OS)
	$(CMP) $(MAIN).o $(DOT_OS) $(FLAGS) -o $(EXEC)

$(MAIN).o: $(MAIN).cpp $(HEADERS)
	$(CMP) -c $(MAIN).cpp $(FLAGS)
$(FUNC1).o: $(FUNC1).cpp
	$(CMP) -c $(FUNC1).cpp	$(FLAGS)
$(FUNC2).o: $(FUNC2).cpp
	$(CMP) -c $(FUNC2).cpp $(FLAGS)
$(FUNC3).o: = $(FUNC3).cpp
	$(CMP) -c $(FUNC3).cpp $(FLAGS)
$(FUNC4).o: = $(FUNC4).cpp
	$(CMP) -c $(FUNC4).cpp $(FLAGS)
$(FUNC5).o: =$(FUNC5).cpp
	$(CMP) -c $(FUNC5).cpp $(FLAGS)
$(FUNC6).o: = $(FUNC6).cpp
	$(CMP) -c $(FUNC6).cpp $(FLAGS)
$(FUNC7).o: = $(FUNC7).cpp
	$(CMP) -c $(FUNC7).cpp $(FLAGS)
$(FUNC8).o: = $(FUNC8).cpp
	$(CMP) -c $(FUNC8).cpp $(FLAGS)
$(FUNC9).o: = $(FUNC9).cpp
	$(CMP) -c $(FUNC9).cpp $(FLAGS)
$(FUNC10).o:  $(FUNC10).cpp
	$(CMP) -c $(FUNC10).cpp $(FLAGS)
$(FUNC11).o: $(FUNC11).cpp
	$(CMP) -c $(FUNC11).cpp $(FLAGS)
$(FUNC12).o: $(FUNC12).cpp
	$(CMP) -c $(FUNC12).cpp $(FLAGS)
$(FUNC13).o: $(FUNC13).cpp
	$(CMP) -c $(FUNC13).cpp $(FLAGS)
$(FUNC14).o: $(FUNC14).cpp
	$(CMP) -c $(FUNC14).cpp $(FLAGS)
$(FUNC15).o: $(FUNC15).cpp
	$(CMP) -c $(FUNC15).cpp $(FLAGS)
$(FUNC16).o: $(FUNC16).cpp
	$(CMP) -c $(FUNC16).cpp $(FLAGS)
$(FUNC17).o: $(FUNC17).cpp
	$(CMP) -c $(FUNC17).cpp $(FLAGS)
$(FUNC18).o: $(FUNC18).cpp
	$(CMP) -c $(FUNC18).cpp $(FLAGS)
$(FUNC19).o: $(FUNC19).cpp
	$(CMP) -c $(FUNC19).cpp $(FLAGS)
$(FUNC20).o: $(FUNC20).cpp
	$(CMP) -c $(FUNC20).cpp $(FLAGS)
$(FUNC21).o: $(FUNC21).cpp
	$(CMP) -c $(FUNC21).cpp $(FLAGS)

clean:
	rm *.o $(EXEC) *~

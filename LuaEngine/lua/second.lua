modID = "BaseGame"
mods[modID] = true

--add item types
item[modID] = {}

item[modID].ironPlate = {}
item[modID].ironGear = {}

--add component types
component[modID] = {}

component[modID].basicDataStore = {
  a = types.double,
  b = types.long
}

--add entity types
entity[modID] = {}

entity[modID].crafter = {
	number = types.double,
	number2 = types.double,
	onCreate = function(self)
		self.number = 0
		self.number2 = 1
	end,
	update = function(self)
		self.number = self.number + 1
		self.number2 = self.number2 * 2
		print(self.number)
		print(self.number2)
	end
}

entity[modID].fibonacci = {
	a = types.int,
	b = types.int,
	onCreate = function(self)
		self.a = 0
		self.b = 1
	end,
	update = function(self)
		local new = self.a + self.b
		self.a = self.b
		self.b = new
		print(new)
	end,
	onDestroy = function(self)
		self.a = 1
	end
}

crying = function()
	print("crying")
end

entity[modID].functionTest = {
	a = types.func,
	onCreate = function(self)
		self.a = crying
	end,
	update = function(self)
		self.a()
	end
}

entity[modID].componentTest = {
  a = types.component,
  onCreate = function(self)
    local comp = init_component(0)
    comp.a = 0
    comp.b = 1
    self.a = comp
  end,
  update = function(self)
  local comp = self.a
    comp.a = comp.a + 1
		comp.b = comp.b * 2
		print(comp.a)
		print(comp.b)
  end
}

--add recipe types
recipe[modID] = {}

recipe[modID].ironGear = {
	input = {mod = modID, type = "ironPlate" , quantity = 1},
	output = {mod = modID, type = "ironGear", quantity = 1},
	time = 1
}
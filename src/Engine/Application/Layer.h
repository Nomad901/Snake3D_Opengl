#pragma once



class Layer
{
public:
	Layer(std::string_view pNameLayer)
		: mNameLayer{pNameLayer}
	{ }
	virtual ~Layer() = default;

	virtual void onUpdate() {}
	virtual void onImGuiRender() {}

	const std::string& getNameLayer() const noexcept 
	{ 
		return mNameLayer;
	}

private:
	std::string mNameLayer;
};
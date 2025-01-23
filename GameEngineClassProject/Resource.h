#pragma once
class Resource
{
public:
	Resource() { m_value = 0; }

	int GetValue() { return m_value; }
	void SetValue(int _number) { m_value = _number; }

	void Reset() { m_value = 0; }

private:
	int m_value;
};


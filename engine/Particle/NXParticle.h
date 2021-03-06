/*
 *  File:    NXParticle.h
 *
 *  author:  张雄(zhang xiong, 1025679612@qq.com)
 *  date:    2017_04_13
 *  purpose: define a particle
 */

#pragma once

#include <vector>

#include "../math/NXVector.h"
#include "../math/NXMatrix.h"
#include "../entity/NXIEntity.h"


namespace NX {
	class Particle {
	public:
		struct Vertex{
			Vertex(float _x, float _y, float _z, float _u, float _v) {
				x = _x, y = _y, z = _z;
				u = _u, v = _v;
			}

			Vertex() = default;

			float x, y, z;     //position
			float u, v;        //texcoord
		};

	public:
		Particle(const int iTextureIndex, const float3 &_Rotation, const float3 &_Position, const float3 &_Acceleration, const float3 &_AngularAcceleration, 
			const float3 &_Velocity, const float3 &_AngularVelocity, const float _LiveTime,  const float2 &_Size);
		Particle() = default;
		virtual ~Particle();

	public:
		virtual void OnTick(const float fDelta);
		virtual void Reset(const int iTextureIndex, const float3 &_Rotation, const float3 &_Position, const float3 &_Acceleration, const float3 &_AngularAcceleration,
			const float3 &_Velocity, const float3 &_AngularVelocity, const float _LiveTime, const float2 &_Size);
		virtual std::vector<Vertex> GetVertex();
		virtual std::vector<int>    GetVertexIndex();
		virtual int FillVertexBuffer(void *pBase) const;
		virtual int FillIndexBuffer(void *pBase, const int iStartIndex) const;

	public:
		Particle& SetTextureIndex(const int TextureIndex);

		Particle& SetRotation(const float3 &_Rotation);
		Particle& SetRotation(const float _rx, const float _ry, const float _rz);
		Particle& AddRotation(const float _arx, const float _ary, const float _arz);
		Particle& AddRotation(const float3 &_addRotation);

		Particle& SetPosition(const float3 &_Position);
		Particle& SetPosition(const float _x, const float _y, const float _z);
		Particle& AddPosition(const float _ax, const float _ay, const float _az);
		Particle& AddPosition(const float3 &_addPosition);

		Particle& SetAcceleration(const float3 &_Acceleration);
		Particle& SetAcceleration(const float _acx, const float _acy, const float _acz);
		Particle& AddAcceleration(const float _aacx, const float _aacy, const float _aacz);
		Particle& AddAcceleration(const float3 &_addAcceleration);

		Particle& SetAngularAcceleration(const float3 &_Acceleration);
		Particle& SetAngularAcceleration(const float _acx, const float _acy, const float _acz);
		Particle& AddAngularAcceleration(const float _aacx, const float _aacy, const float _aacz);
		Particle& AddAngularAcceleration(const float3 &_addAcceleration);

		Particle& SetVelocity(const float3 &_Velocity);
		Particle& SetVelocity(const float _vx, const float _vy, const float _vz);
		Particle& AddVelocity(const float _avx, const float _avy, const float _avz);
		Particle& AddVelocity(const float3 &_addVelocity);

		Particle& SetAngularVelocity(const float3 &_Velocity);
		Particle& SetAngularVelocity(const float _vx, const float _vy, const float _vz);
		Particle& AddAngularVelocity(const float _avx, const float _avy, const float _avz);
		Particle& AddAngularVelocity(const float3 &_addVelocity);

		Particle& SetLiveTime(const float _LiveTime);
		Particle& AddLiveTime(const float _addLiveTime);

		Particle& SetSize(const float2 &_Size);
		Particle& SetDied(const bool bDied);

	public:
		int              GetTextureIndex() const;
		const float3&    GetRotation() const;
		const float3&    GetPosition() const;
		const float3&    GetAcceleration() const;
		const float3&    GetAngularAcceleration() const;
		const float3&    GetVelocity() const;
		const float3&    GetAngularVelocity() const;
		float            GetLiveTime() const;
		float            GetTimeElapsed() const;
		const float2&    GetSize() const;
		bool             IsDied() const;

	private:
		int              m_iTextureIndex;         //texture index of the particle texture set
		float3           m_Rotation;              //init rotation(radian)
		float3           m_Position;              //init position
		float3           m_Acceleration;          //position acceleration
		float3           m_Angularcceleration;    //angular acceleration
		float3           m_Velocity;              //velocity
		float3           m_AngularVelocity;       //angular velocity
		float            m_fLiveTime;             //time of the particle's life
		float            m_fTimeElapsed;          //time elapsed
		float2           m_Size;                  //size of the particle
		bool             m_bDied;                 //particle is died, we needn't render it any more
	};
}
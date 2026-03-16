const exposes = require('zigbee-herdsman-converters/lib/exposes');
const e = exposes.presets;
const ea = exposes.access;

const fzGas = {
    cluster: 'seMetering',
    type: ['attributeReport', 'readResponse'],
    convert: (model, msg, publish, options, meta) => {
        console.log('seMetering data:', JSON.stringify(msg.data));
        
        if (msg.data['currentSummDelivered'] !== undefined) {
            const raw = msg.data['currentSummDelivered'];
            console.log('currentSummDelivered raw:', raw, typeof raw);
            const divisor = msg.data['divisor'] || 100;
            const multiplier = msg.data['multiplier'] || 1;
            const value = Number(raw) * multiplier / divisor;
            return { gas: value };
        }
    },
};

const definition = {
    zigbeeModel: ['ESP32H2GasCounter'],
    model: 'ESP32H2GasCounter',
    vendor: 'Custom devices',
    description: 'Zigbee Gas meter',
    ota: true,
    fromZigbee: [fzGas],
    toZigbee: [],
    exposes: [
        e.numeric('gas', ea.STATE)
            .withUnit('m³')
            .withDescription('Total gas consumption in m³'),
    ],
    configure: async (device, coordinatorEndpoint) => {
        const endpoint = device.getEndpoint(1);
        await endpoint.read('seMetering', ['multiplier', 'divisor']);
    },
};

module.exports = definition;
const exposes = require('zigbee-herdsman-converters/lib/exposes');
const e = exposes.presets;
const ea = exposes.access;

const fzGas = {
    cluster: 'seMetering',
    type: ['attributeReport', 'readResponse'],
    convert: (model, msg, publish, options, meta) => {
        console.log('>>> fzGas called');
        console.log('>>> msg.data:', JSON.stringify(msg.data));

        if (msg.data['currentSummDelivered'] !== undefined) {
            const raw = msg.data['currentSummDelivered'];

            // UINT48 as array [low, high]
            let rawValue;
            if (Array.isArray(raw)) {
                rawValue = raw[0] + raw[1] * 0x100000000;
            } else {
                rawValue = Number(raw);
            }

            const divisor = msg.data['divisor'] || 100;
            const multiplier = msg.data['multiplier'] || 1;
            const value = rawValue * multiplier / divisor;

            console.log('>>> gas value:', value);
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

        // Read multiplier/divisor
        await endpoint.read('seMetering', ['multiplier', 'divisor']);

        // Link reporting
        await endpoint.bind('seMetering', coordinatorEndpoint);
        await endpoint.configureReporting('seMetering', [{
            attribute: 'currentSummDelivered',
            minimumReportInterval: 0,
            maximumReportInterval: 3600,
            reportableChange: 1,
        }]);
    },
};

module.exports = definition;